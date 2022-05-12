#include "templatesmenu.h"
#include "ui_templatesmenu.h"
#include "dialogdir.h"
#include "dialogfile.h"
#include "dialogfile.h"
#include "formphplanguage.h"
#include "formcpplanguage.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <unordered_map>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QTreeWidget>

// TODO LIST
// Create file +
// Create dir +
// Rewrite file +
// Unselect +
// Delete +


// Create JSON +
// Save JSON +
// Edit JSON -+

TemplatesMenu::TemplatesMenu(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TemplatesMenu)
{
  ui->setupUi(this);
  QRegularExpression re("\\w{15}");
  ui->le_name_template->setValidator(new QRegularExpressionValidator(re, this));
  dollar_writer = new DollarWriter();
  dollar_writer->create_template_storage();
}

TemplatesMenu::~TemplatesMenu()
{
  delete ui;
  delete dollar_writer;
}

void TemplatesMenu::on_pb_reset_clicked()
{
  QMessageBox::StandardButton reply = QMessageBox::question(this, "Question", "Are you sure?",
                                                           QMessageBox::Yes | QMessageBox::No);
  if ( reply == QMessageBox::Yes)
  {
    // Set none comboBox
    ui->comb_project_language->setCurrentIndex(0);
    delete language_form;

    // Clear txt lineEdit
    ui->le_name_template->clear();

    // Clear file-tree
    ui->treeW_project_struct->clear();
  }
}


void TemplatesMenu::on_pb_create_dir_clicked()
{
  file_dialog = new DialogDir(this);
  connect(static_cast<DialogDir*>(file_dialog), &DialogDir::dir_info, this, &TemplatesMenu::create_dir_in_tree);
  file_dialog->show();
}


void TemplatesMenu::on_pb_create_file_clicked()
{
  file_dialog = new DialogFile(this);

  connect(static_cast<DialogFile*>(file_dialog), &DialogFile::file_info, this, &TemplatesMenu::create_file_in_tree);
  file_dialog->show();
}


void TemplatesMenu::on_pb_delete_clicked()
{
  if ( !check_select_in_tree() ) { return; }

  if( ui->treeW_project_struct->selectedItems().at(ColumnIndex::Type)->text(0) == list_type_file[TypeFile::Dir] or
       ui->treeW_project_struct->selectedItems().at(ColumnIndex::Type)->text(0) == list_type_file[TypeFile::File])
  {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Question", "Are you sure?",
                                                             QMessageBox::Yes | QMessageBox::No);
    if ( reply == QMessageBox::Yes)
    {
      delete ui->treeW_project_struct->selectedItems().at(0);
    }
  }
  else
  {
    QMessageBox::critical(this, "Error", "Select file or dir!");
  }
}

bool TemplatesMenu::check_select_in_tree()
{
  if( ui->treeW_project_struct->selectedItems().isEmpty())
  {
    /// Message box error select item
    QMessageBox::critical(this, "Error", "Select item!");
    return false;
  }
  else
  {
    return true;
  }
}

bool TemplatesMenu::check_select_in_tree_file()
{
  if ( !check_select_in_tree()) { return false; }

  if( ui->treeW_project_struct->selectedItems().at(ColumnIndex::Type)->text(0) != list_type_file[TypeFile::File])
  {
    QMessageBox::critical(this, "Error", "Select file!");
    return false;
  }
  else
  {
    return true;
  }
}

bool TemplatesMenu::check_select_in_tree_dir()
{
  if ( !check_select_in_tree()) { return false; }

  if( ui->treeW_project_struct->selectedItems().at(ColumnIndex::Type)->text(0) != list_type_file[TypeFile::Dir])
  {
    QMessageBox::critical(this, "Error", "Select dir!");
    return false;
  }
  else
  {
    return true;
  }
}

void TemplatesMenu::rename_dir(const QString &str)
{
  auto item = ui->treeW_project_struct->selectedItems().at(0);
  item->setText(ColumnIndex::Name, str);
}

void TemplatesMenu::rename_file(const QStringList &str)
{
  auto item = ui->treeW_project_struct->selectedItems().at(0);
  item->setText(ColumnIndex::Name, str.at(0));
  item->child(0)->setText(ColumnIndex::Name, str.at(1));
}

void TemplatesMenu::create_discription_in_file(const QString& str, QTreeWidgetItem* file)
{
  auto item = new QTreeWidgetItem(file);
  item->setText(ColumnIndex::Type, list_type_file[TypeFile::Content]);
  item->setTextAlignment(ColumnIndex::Type, Qt::AlignTop);
  item->setText(ColumnIndex::Name, str);
}

void TemplatesMenu::on_pb_unselect_clicked()
{
  ui->treeW_project_struct->clearSelection();
}

//QJsonObject TemplatesMenu::parse_tree_to_json(QTreeWidgetItem *item, size_t index)
//{
//  qDebug() << index << "] " << item->text(ColumnIndex::Type)  << item->text(ColumnIndex::Name);
//  for( int i = 0; i < item->childCount(); ++i ){
//    parse_tree_to_json( item->child(i), ++index);
//  }
//  return QJsonObject();
//}

// ["Dir:", "1", []], ["File:", "main.cpp", ["Content:", "afdsf"]]]
QJsonArray TemplatesMenu::create_json_project_struct(QTreeWidgetItem *tree)
{
  QJsonArray arr;
  arr.append(tree->text(ColumnIndex::Type));
  arr.append(tree->text(ColumnIndex::Name));
  // Перебераем детей
  for(int i{0}; i < tree->childCount(); ++i)
  {
    arr.push_back(create_json_project_struct(tree->child(i)));
  }

  return arr;
}

void TemplatesMenu::set_project_struct(QJsonArray *json)
{

}

/*
 * f(QJsonObject* p, QTreeWidgetItem* tree)
 * {
 * 	если (tree.ест_детей())
 * 	{
 * 		f(p, tree.child(0));
 * 	}
 * }
 *
 */

void TemplatesMenu::on_pb_confirm_clicked()
{
  QJsonObject* template_json = new QJsonObject();
  template_json->insert("name", ui->le_name_template->text());
  template_json->insert("language", ui->comb_project_language->currentText());

  if ( auto cpp_form = dynamic_cast<FormCppLanguage*>(language_form))
  {
    template_json->insert("build_system", cpp_form->build_system());
    QJsonArray arr;
    for (auto i: cpp_form->list_libs())
      arr.push_back(i);

    template_json->insert("libraries", arr);
  }
  else if ( auto php_form = dynamic_cast<FormPhpLanguage*>(language_form) )
  {
    QJsonArray arr;
    for (auto i: php_form->list_libs())
      arr.push_back(i);

    template_json->insert("libraries", arr);
  }

  template_json->insert("struct", create_json_project_struct(ui->treeW_project_struct->invisibleRootItem()));
  if ( dollar_writer->save_template(QJsonDocument(*template_json), template_json->value("name").toString()) )
    QMessageBox::about(this, "Success", "File write");
  else
    QMessageBox::about(this, "Error", "File not write");
}


/*
{
  "name": "Dollar",
  "language": "C++",
  "build_system": "CMake",
  "libraries":
    [
    "Qt",
    "SFML"
    ]
  "struct":
    [
      {
        "name": "Hello",
        "type": "d",
        "children": []
      },
      {
        "name": "Hello2",
        "type": "d",
        "children":
          [
            {
              "name": "Arividerci",
              "type": "d",
              "children":
                [
                  {
                    "name": "Hi.cpp",
                    "type": "f",
                    "content": "1231 123 123 \n 123"
                  }
                ]
            }
          ]
      },
      {
        "name": "Adios",
        "type": "d",
        "children": []
      }
    ]
}
*/


//void TemplatesMenu::on_pb_write_in_file_clicked()
//{
//  if(check_select_in_tree_file())
//  {
//    file_dialog = new DialogWriteInFile(this, ui->treeW_project_struct->selectedItems().at(0)->text(0).mid(3));

//    connect(static_cast<DialogWriteInFile*>(file_dialog), &DialogWriteInFile::info_dialog, this, &TemplatesMenu::info_dialog);
//    file_dialog->show();
//  }
//}

void TemplatesMenu::create_dir_in_tree(const QString &str)
{
  auto items = ui->treeW_project_struct->selectedItems();
  if( items.isEmpty())
  {
    auto item = new QTreeWidgetItem(ui->treeW_project_struct);
    item->setText(ColumnIndex::Name, str);
    item->setText(ColumnIndex::Type, list_type_file[TypeFile::Dir]);
  }
  else if ( check_select_in_tree_dir())
  {
    auto item = new QTreeWidgetItem(items.at(0));
    item->setText(ColumnIndex::Name, str);
    item->setText(ColumnIndex::Type, list_type_file[TypeFile::Dir]);
  }
}

void TemplatesMenu::create_file_in_tree(const QStringList &str)
{
  auto items = ui->treeW_project_struct->selectedItems();
  if( items.isEmpty())
  {
    auto item = new QTreeWidgetItem(ui->treeW_project_struct);
    item->setText(ColumnIndex::Name, str.at(0));
    item->setText(ColumnIndex::Type, list_type_file[TypeFile::File]);
    create_discription_in_file(str.at(1), item);
  }
  else if ( check_select_in_tree_dir())
  {
    auto item = new QTreeWidgetItem(items.at(0));
    item->setText(ColumnIndex::Name, str.at(0));
    item->setText(ColumnIndex::Type, list_type_file[TypeFile::File]);
    create_discription_in_file(str.at(1), item);
  }
}


void TemplatesMenu::on_pb_rewrite_file_clicked()
{
  if ( check_select_in_tree())
  {
    if(ui->treeW_project_struct->selectedItems().at(ColumnIndex::Type)->text(0) == list_type_file[TypeFile::Dir])
    {
      file_dialog = new DialogDir(this);
      connect(this, &TemplatesMenu::dir_name, static_cast<DialogDir*>(file_dialog), &DialogDir::set_dir_name);
      connect(static_cast<DialogDir*>(file_dialog), &DialogDir::dir_info, this, &TemplatesMenu::rename_dir);
      emit dir_name(ui->treeW_project_struct->selectedItems().at(0)->text(ColumnIndex::Name));
      file_dialog->show();
    }
    else if (ui->treeW_project_struct->selectedItems().at(ColumnIndex::Type)->text(0) == list_type_file[TypeFile::File])
    {
      file_dialog = new DialogFile(this);
      connect(this, &TemplatesMenu::file_name, static_cast<DialogFile*>(file_dialog), &DialogFile::set_file_name);
      connect(this, &TemplatesMenu::file_content, static_cast<DialogFile*>(file_dialog), &DialogFile::set_file_content);
      connect(static_cast<DialogFile*>(file_dialog), &DialogFile::file_info, this, &TemplatesMenu::rename_file);

      emit file_name(ui->treeW_project_struct->selectedItems().at(0)->text(ColumnIndex::Name));
      emit file_content(ui->treeW_project_struct->selectedItems().at(0)->child(0)->text(ColumnIndex::Name));
      file_dialog->show();
    }
    else
    {
      QMessageBox::critical(this, "Error", "This can't be rewrite");
    }
  }
}


void TemplatesMenu::on_comb_project_language_textActivated(const QString &arg1)
{
  if ( !ui->gridLayout_language_form->isEmpty())
  {
    delete language_form;
    language_form = nullptr;
  }

  if ( arg1 == "C++" )
  {
    ui->comb_project_language->setCurrentIndex(1);
    language_form = new FormCppLanguage();
  }
  else if ( arg1 == "PHP" )
  {
    ui->comb_project_language->setCurrentIndex(2);
    language_form = new FormPhpLanguage();
  }
  else if ( arg1 == "None")
  {
    ui->comb_project_language->setCurrentIndex(0);
    if (language_form)
      delete language_form;
    return;
  }

  ui->gridLayout_language_form->addWidget(language_form);
}


void TemplatesMenu::on_pb_select_template_clicked()
{
  const QString file_name = QFileDialog::getOpenFileName(this, "Open file", dollar_writer->way_to_storage_templates(), "*.json");

  QFile jsonFile(file_name);
  if (!jsonFile.open(QFile::ReadOnly) )
  {
    QMessageBox::warning(this, "Error", "The file was not opened");
    return;
  }

  // Set none comboBox
  ui->comb_project_language->setCurrentIndex(0);
  delete language_form;

  // Clear txt lineEdit
  ui->le_name_template->clear();

  // Clear file-tree
  ui->treeW_project_struct->clear();

  QJsonObject template_file = QJsonDocument().fromJson(jsonFile.readAll()).object();

  ui->le_name_template->setText(template_file.value("name").toString());
  ui->comb_project_language->textActivated(template_file.value("language").toString());
  if ( auto cpp_form = dynamic_cast<FormCppLanguage*>(language_form))
  {
    cpp_form->set_build_system(template_file.value("build_system").toString());
    QStringList libs;
    QJsonArray lib_in_file = template_file.value("libraries").toArray();

    for (auto lib : lib_in_file)
      libs.push_back(lib.toString());
    cpp_form->set_list_libs(libs);
  }
  else if ( auto php_form = dynamic_cast<FormPhpLanguage*>(language_form) )
  {
    QStringList libs;
    QJsonArray lib_in_file = template_file.value("libraries").toArray();

    for (auto lib : lib_in_file)
      libs.push_back(lib.toString());
    php_form->set_list_libs(libs);
  }


}

