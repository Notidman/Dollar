#include "dialognamedir.h"
#include <QMessageBox>
#include "ui_dialognamedir.h"

DialogNameDir::DialogNameDir(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogNameDir)
{
  ui->setupUi(this);
}

DialogNameDir::~DialogNameDir()
{
  delete ui;
}

void DialogNameDir::on_buttonBox_accepted()
{
  if( ui->lineEdit->text() != "" )
    emit name_item("d: " + ui->lineEdit->text());
  else
  {
    QMessageBox::critical(this, "Error", "The file cannot be without a name!");
  }
}

