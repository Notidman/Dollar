#include "projectsmenu.h"
#include "ui_projectsmenu.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

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
  QDir dir(ui->lEdit_project_path->text());
  if( dir.mkdir(ui->lEdit_project_name->text()) )
  {
    qDebug() << "Created project dir!";
  }

  QJsonDocument json = dollar_writer->load_template(ui->lEdit_template_name->text());
  qDebug() << "Load json!";
}

