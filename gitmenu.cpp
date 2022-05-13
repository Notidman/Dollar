#include "gitmenu.h"
#include "ui_gitmenu.h"

#include <QFileDialog>
#include <QStandardPaths>

GitMenu::GitMenu(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GitMenu)
{
  ui->setupUi(this);
}

GitMenu::~GitMenu()
{
  delete ui;
}

void GitMenu::on_pushButton_clicked()
{
  const QString file_name = QFileDialog::getExistingDirectory(this, "Open Dir", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
  ui->lEdit_project_path->setText(file_name);
}

