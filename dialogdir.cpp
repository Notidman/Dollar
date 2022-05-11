#include "dialogdir.h"
#include "ui_dialogdir.h"
#include <QMessageBox>

DialogDir::DialogDir(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogNameDir)
{
  ui->setupUi(this);
}

DialogDir::~DialogDir()
{
  delete ui;
}

void DialogDir::on_buttonBox_accepted()
{
  if( ui->lineEdit->text() == "" )
  {
    QMessageBox::critical(this, "Error", "The file cannot be without a name!");
    return;
  }

  emit dir_info(ui->lineEdit->text());
}

void DialogDir::set_dir_name(const QString &str)
{
  ui->lineEdit->setText(str);
}

