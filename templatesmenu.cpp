#include "templatesmenu.h"
#include "ui_templatesmenu.h"
#include "dialognamedir.h"
#include "dialognamefile.h"
#include "dialognamenew.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

TemplatesMenu::TemplatesMenu(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TemplatesMenu)
{
  ui->setupUi(this);
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
    // Clear list libs
    ui->checkBox_OpenCV->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_Qt->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_SDL->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBox_SFML->setCheckState(Qt::CheckState::Unchecked);

    // Set none comboBox
    ui->comb_build_system->setCurrentIndex(0);
    ui->comb_control_system->setCurrentIndex(0);

    // Clear txt lineEdit
    ui->le_name_template->clear();
    ui->le_project_lang->clear();
    ui->le_project_tag->clear();

    // Clear file-tree
    ui->treeW_project_struct->clear();
  }
}


void TemplatesMenu::on_pb_create_dir_clicked()
{
  file_dialog = new DialogNameDir(this);
  connect(static_cast<DialogNameDir*>(file_dialog), &DialogNameDir::name_item, this, &TemplatesMenu::name_item);
  file_dialog->setWindowModality(Qt::WindowModality::ApplicationModal);
  file_dialog->show();
}


void TemplatesMenu::on_pb_create_file_clicked()
{
  file_dialog = new DialogNameFile(this);

  connect(static_cast<DialogNameFile*>(file_dialog), &DialogNameFile::name_item, this, &TemplatesMenu::name_item);
  file_dialog->setWindowModality(Qt::WindowModality::ApplicationModal);
  file_dialog->show();
}


void TemplatesMenu::on_pb_delete_clicked()
{
  auto items = ui->treeW_project_struct->selectedItems();
  if( items.isEmpty())
  {
    QMessageBox::critical(this, "Error", "Select file!");
  }
  else
  {
    delete items.at(0);
  }
}


void TemplatesMenu::on_pb_rename_file_clicked()
{
  auto items = ui->treeW_project_struct->selectedItems();
  if( items.isEmpty())
  {
    /// Message box error select item
    QMessageBox::critical(this, "Error", "Select file!");
  }
  else
  {
    file_dialog = new DialogNameNew(this, items.at(0)->text(0).mid(3));

    connect(static_cast<DialogNameNew*>(file_dialog), &DialogNameNew::name_item, this, &TemplatesMenu::name_item);
    file_dialog->setWindowModality(Qt::WindowModality::ApplicationModal);
    file_dialog->show();
  }
}

void TemplatesMenu::name_item(QString str)
{
  if ( auto _ = dynamic_cast<DialogNameDir*>(file_dialog))
  {
    create_item_in_tree(str);
  }
  else if ( auto _ = dynamic_cast<DialogNameFile*>(file_dialog))
  {
    create_item_in_tree(str);
  }
  else if ( auto _ = dynamic_cast<DialogNameNew*>(file_dialog))
  {
    auto item = ui->treeW_project_struct->selectedItems().at(0);
    if ( item->text(0).at(0) == 'f')
    {
      item->setText(0, "f: " + str);
    }
    else if ( item->text(0).at(0) == 'd')
    {
      item->setText(0, "d: " + str);
    }

  }
}


void TemplatesMenu::on_pb_unselect_clicked()
{
  ui->treeW_project_struct->clearSelection();
}

void TemplatesMenu::create_item_in_tree(QString str)
{
  auto items = ui->treeW_project_struct->selectedItems();
  if( items.isEmpty())
  {
    auto item = new QTreeWidgetItem(ui->treeW_project_struct);
    item->setText(0, str);
  }
  else if ( items.at(0)->text(0).at(0) != 'f')
  {
    auto item = new QTreeWidgetItem(items.at(0));
    item->setText(0, str);
  }
  else
  {
    QMessageBox::critical(this, "Error", "You can't create in!");
  }
}

void TemplatesMenu::on_pb_set_defauilt_path_clicked()
{

}

