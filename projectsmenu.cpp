#include "projectsmenu.h"
#include "ui_projectsmenu.h"
#include "structsprojectsenums.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <git2/repository.h>
#include <git2/errors.h>
#include <git2/global.h>


// Create func find all sub dir in json file and add it in CMake

ProjectsMenu::ProjectsMenu(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ProjectsMenu)
{
  ui->setupUi(this);
  QRegularExpression re("\\w{15}");
  ui->lEdit_project_name->setValidator(new QRegularExpressionValidator(re, this));
  dollar_writer = new DollarWriter();
}

ProjectsMenu::~ProjectsMenu()
{
  delete ui;
}

void ProjectsMenu::on_pb_reset_clicked()
{
  ui->lEdit_project_name->clear();
  ui->lEdit_project_path->clear();
  ui->lEdit_drc_way->clear();
}

void ProjectsMenu::on_pb_select_template_clicked()
{
  const QString file_name = QFileDialog::getOpenFileName(this, "Open file", dollar_writer->way_to_storage_templates(), "*.drc");
  ui->lEdit_drc_way->setText(file_name);
}


void ProjectsMenu::on_pb_select_path_clicked()
{
  const QString file_name = QFileDialog::getExistingDirectory(this, "Open Dir",
                                                              QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
  ui->lEdit_project_path->setText(file_name);
}


void ProjectsMenu::on_pb_create_clicked()
{
  if ( ui->lEdit_project_name->text().isEmpty() )
  {
    QMessageBox::warning(this, "Error", "Project name can't be empty!");
    return;
  }

  if ( ui->lEdit_project_path->text().isEmpty() )
  {
    QMessageBox::warning(this, "Error", "Project path can't be empty!");
    return;
  }

  if ( ui->lEdit_drc_way->text().isEmpty() )
  {
    QMessageBox::warning(this, "Error", "Template name can't be empty!");
    return;
  }

  QString project_path = ui->lEdit_project_path->text();
  QString project_name = ui->lEdit_project_name->text();
  QString way = project_path + '/' + project_name;

  QDir dir(project_path);
  if( dir.mkdir(project_name) )
  {
    qDebug() << "Created project dir!";
  }

  dollar_writer->create_tmp_dir(ui->lEdit_drc_way->text());

  QJsonObject json = dollar_writer->load_metafile(dollar_writer->get_way_metafile()).object();
  qDebug() << "Load json! " << json.value(jsonkeys::name).toString();

  QString language_project = json.value(jsonkeys::language).toString();
  if ( language_project == "C++")
  {
    QString build_sys = json.value(jsonkeys::build_system).toString();
    if ( build_sys == "CMake")
      gen_cmake_cpp(way);
  }
  else if ( language_project == "C")
  {
    QString build_sys = json.value(jsonkeys::build_system).toString();
    if ( build_sys == "CMake")
      gen_cmake_c(way);
  }

  if (json.value(jsonkeys::control_version).toString() == "Git")
  {
    gen_git(way);
  }

  create_project_struct(json.value(jsonkeys::struct_pj).toArray(), way);

  QMessageBox::about(this, "Success", "Project was be created");

  dollar_writer->remove_tmp_dir();

  // clear old data
  ui->lEdit_project_name->setText("");
  ui->lEdit_project_path->setText("");
  ui->lEdit_drc_way->setText("");
}

void ProjectsMenu::create_project_struct(const QJsonArray& array, const QString& path)
{
  for(int i = 0; i < array.count(); ++i)
  {
    create_project_element(array.at(i).toObject(), path);
  }
}

void ProjectsMenu::create_project_element(const QJsonObject& json, const QString& path)
{
  auto type = json.value(jsonkeys::struct_pj_type).toString();
  auto name = json.value(jsonkeys::struct_pj_name).toString();

  if( type == map_type_file[TypeFile::Dir])
  {
    QDir dir(path);
    dir.mkdir(name);
    create_project_struct(json.value(jsonkeys::struct_pj_childr).toArray(), path + '/' + name);
  }
  else if ( type == map_type_file[TypeFile::File])
  {
    QFile file(path + '/' + name);
    file.open(QFile::WriteOnly);
    file.write(json.value(jsonkeys::struct_pj_childr).toArray()
               .at(0).toObject().value(jsonkeys::struct_pj_name).toString().toUtf8());
    file.close();
  }
  else if ( type == map_type_file[TypeFile::ExternalFile])
  {
    QFile::copy(dollar_writer->way_tmp_dir() + '/' + name,
                path + '/' + name);
  }
}

void ProjectsMenu::gen_git(const QString &path)
{
   if ( git_libgit2_init() )
   {
     git_repository *rep = NULL;
     int error = git_repository_init(&rep, path.toStdString().c_str(), false);
     if (error < 0)
     {
       const git_error *e = git_error_last();
       QMessageBox::critical(this, QString(error) + ' ' + QString(e->klass), e->message);
       exit(error);
     }
   }
   else
   {
     QMessageBox::critical(this, "Error", "Git init error!");
   }
}

void ProjectsMenu::gen_cmake_c(const QString &path, const QStringList &libs)
{
  QFile file_cmake(path + "/CMakeLists.txt");
  file_cmake.open(QFile::WriteOnly);
  file_cmake.write(QString(
"cmake_minimum_required(VERSION 3.2)\n\
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\
project(" + ui->lEdit_project_name->text() + " LANGUAGES C)\n\
set(CMAKE_C_STANDARD 18)\n\
set(CMAKE_C_FLAGS \"${CMAKE_C_FLAGS} -std=c18 -Werror -Wall -Wextra -Wpedantic -fPIC -march=native -pthread -g\")\n\
set(CMAKE_C_FLAGS_RELEASE \"-std=c18 -O2 -fPIC -march=native -pthread\")\n\
include_directories(${DIR_FILES})\n\
set(PROJECT_SOURCES_DIR ${DIR_FILES})\n\
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.c)\n\
add_executable(${PROJECT_NAME} ${SOURCES})"
                     ).toUtf8()
   );
   qDebug() << "CMake created!";
}

void ProjectsMenu::gen_cmake_cpp(const QString &path, const QStringList& libs)
{
  QFile file_cmake(path + "/CMakeLists.txt");
  file_cmake.open(QFile::WriteOnly);
  file_cmake.write(
        QString(
"cmake_minimum_required(VERSION 3.2)\n\
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\
project(" + ui->lEdit_project_name->text() + " LANGUAGES CXX)\n\
set(CMAKE_CXX_STANDARD 20)\n\
set(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} -std=c++20 -Werror -Wall -Wextra -Wpedantic -fPIC -march=native -pthread -g\")\n\
set(CMAKE_CXX_FLAGS_RELEASE \"-std=c++20 -O2 -fPIC -march=native -pthread\")\n\
include_directories(${DIR_FILES})\n\
set(PROJECT_SOURCES_DIR ${DIR_FILES})\n\
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)\n\
add_executable(${PROJECT_NAME} ${SOURCES})\n"
        ).toUtf8()
   );
   qDebug() << "CMake created!";
}

//void TemplatesMenu::fill_tree(QTreeWidgetItem *item, const QJsonArray& array)
//{
//  for(int i = 0; i < array.count(); ++i)
//  {
//    parse_element_json(item, array.at(i).toObject());
//  }
//}

//void TemplatesMenu::parse_element_json(QTreeWidgetItem *item, const QJsonObject json)
//{
//  auto type = json.value("Type").toString();
//  auto name = json.value("Name").toString();

//  if( type == map_type_file[TypeFile::Dir])
//  {
//    auto dir_item = new QTreeWidgetItem(item);
//    dir_item->setText(ColumnIndex::Type, type);
//    dir_item->setText(ColumnIndex::Name, name);
//    fill_tree(dir_item, json.value("Children").toArray());
//  }
//  else if ( type == map_type_file[TypeFile::File])
//  {
//    auto file_item = new QTreeWidgetItem(item);
//    file_item->setText(ColumnIndex::Type, type);
//    file_item->setText(ColumnIndex::Name, name);
//    auto content = new QTreeWidgetItem(file_item);
//    content->setText(ColumnIndex::Type,
//                     json.value("Children").toArray().at(0).toObject().value("Type").toString());
//    content->setText(ColumnIndex::Name,
//                     json.value("Children").toArray().at(0).toObject().value("Name").toString());
//  }
//}




// OLD VERSION

//void TemplatesMenu::create_tree_by_json(QJsonArray array)
//{
//  auto root = ui->treeW_project_struct->invisibleRootItem();
//
//  for(int i = 0; i < array.count(); ++i)
//  {
//    qDebug() << array.at(i).toArray();
//    set_project_struct(root, array.at(i).toArray());
//    qDebug() << "--------------------------------";
//  }
//}
//
//void TemplatesMenu::set_project_struct(QTreeWidgetItem *tree, QJsonArray json)
//{
//  if( json.at(0).toString() == list_type_file[TypeFile::Dir])
//  {
//    auto item = new QTreeWidgetItem(tree);
//    item->setText(ColumnIndex::Type, json.at(0).toString());
//    item->setText(ColumnIndex::Name, json.at(1).toString());
//
//    if( json.count() > 2)
//    {
//      for(int i = 0; i < json.count() - 2; ++i)
//        set_project_struct(item, json.at(i+2).toArray());
//    }
//  }
//  else if (json.at(0).toString() == list_type_file[TypeFile::File] )
//  {
//    auto item = new QTreeWidgetItem(tree);
//    item->setText(ColumnIndex::Type, json.at(0).toString());
//    item->setText(ColumnIndex::Name, json.at(1).toString());
//    auto content = new QTreeWidgetItem(item);
//    content->setText(ColumnIndex::Type, json.at(2).toArray().at(0).toString());
//    content->setText(ColumnIndex::Name, json.at(2).toArray().at(1).toString());
//  }
//}
//
//
