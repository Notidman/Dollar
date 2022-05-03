#include "dialognamedir.h"
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
  emit name_item("d: " + ui->lineEdit->text());
}

