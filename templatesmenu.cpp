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

// TODO LIST
// Create file +
// Create dir +
// Rewrite file +
// Unselect +
// Delete +


// Create JSON -
// Save JSON -
// Edit JSON -

TemplatesMenu::TemplatesMenu(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TemplatesMenu)
{
  ui->setupUi(this);
  QRegularExpression re("\\w{15}");
  ui->le_name_template->setValidator(new QRegularExpressionValidator(re, this));
}

TemplatesMenu::~TemplatesMenu()
{
  delete ui;
}

void TemplatesMenu::on_pb_reset_clicked()
{
  QMessageBox::StandardButton reply = QMessageBox::question(this, "Question", "Are you sure?",
                                                           QMessageBox::Yes | QMessageBox::No);
  if ( reply == QMessageBox::Yes)
  {
    // Set none comboBox
    ui->comb_project_language->setCurrentIndex(0);
    language_form.reset();

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

void TemplatesMenu::on_pb_confirm_clicked()
{
}

//void TemplatesMenu::on_pb_write_in_file_clicked()
//{
//  if(check_select_in_tree_file())
//  {
//    file_dialog = new DialogWriteInFile(this, ui->treeW_project_struct->selectedItems().at(0)->text(0).mid(3));

//    connect(static_cast<DialogWriteInFile*>(file_dialog), &DialogWriteInFile::info_dialog, this, &TemplatesMenu::info_dialog);
//    file_dialog->show();
//  }
//}


void TemplatesMenu::on_pb_select_template_clicked()
{

}

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
    language_form.reset();
  }

  if ( arg1 == "C++" ) { language_form = std::make_unique<FormCppLanguage>(); }
  else if ( arg1 == "PHP" ) { language_form = std::make_unique<FormPhpLanguage>(); }
  else if ( arg1 == "None") { language_form.reset(); return; }

  ui->gridLayout_language_form->addWidget(language_form.get());
}

