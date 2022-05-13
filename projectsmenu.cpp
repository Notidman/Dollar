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
  ui->lEdit_template_name->clear();
}

void ProjectsMenu::on_pb_select_template_clicked()
{
  const QString file_name = QFileDialog::getOpenFileName(this, "Open file", dollar_writer->way_to_storage_templates(), "*.json");
  ui->lEdit_template_name->setText(file_name);
}


void ProjectsMenu::on_pb_select_path_clicked()
{
  const QString file_name = QFileDialog::getExistingDirectory(this, "Open Dir", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
  ui->lEdit_project_path->setText(file_name);
}


void ProjectsMenu::on_pb_create_clicked()
{
  if ( ui->lEdit_project_name->size().isEmpty())
  {
    QMessageBox::warning(this, "Error", "Project name can't be empty!");
    return;
  }

  QString project_path = ui->lEdit_project_path->text();
  QString project_name = ui->lEdit_project_name->text();

  QDir dir(project_path);
  if( dir.mkdir(project_name) )
  {
    qDebug() << "Created project dir!";
  }

  QJsonObject json = dollar_writer->load_template(ui->lEdit_template_name->text()).object();
  qDebug() << "Load json! " << json.value("name").toString();

  create_project(json.value("struct").toArray(), project_path + '/' + project_name);
}

void ProjectsMenu::create_project(QJsonArray array, const QString& path)
{
  for(int i = 0; i < array.count(); ++i)
  {
    qDebug() << array.at(i).toArray();
    create_struct_project(path, array.at(i).toArray());
    qDebug() << "--------------------------------";
  }
}

void ProjectsMenu::create_struct_project(QString path, QJsonArray json)
{
  if( json.at(0).toString() == list_type_file[TypeFile::Dir])
  {
    QDir dir(path);
    if( dir.mkdir(json.at(1).toString()) )
    {
      qDebug() << "Created dir! " << json.at(1).toString();
    }

    if( json.count() > 2)
    {
      for(int i = 0; i < json.count() - 2; ++i)
        create_struct_project(path + '/' + json.at(1).toString(), json.at(i+2).toArray());
    }
  }
  else if (json.at(0).toString() == list_type_file[TypeFile::File] )
  {
    QFile file(path + '/' + json.at(1).toString());
    file.open(QFile::WriteOnly);
    file.write(json.at(2).toArray().at(1).toString().toUtf8());
    qDebug() << "Created file! " << json.at(1).toString();
  }
}


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
