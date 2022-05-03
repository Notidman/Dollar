#include "projectsmenu.h"
#include "ui_projectsmenu.h"

ProjectsMenu::ProjectsMenu(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ProjectsMenu)
{
  ui->setupUi(this);
}

ProjectsMenu::~ProjectsMenu()
{
  delete ui;
}

void ProjectsMenu::on_pushButton_3_clicked()
{
  ui->lEdit_project_name->clear();
  ui->lEdit_project_path->clear();

  ui->colView_templates->reset();
}

