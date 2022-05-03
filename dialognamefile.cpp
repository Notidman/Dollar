#include "dialognamefile.h"
#include "ui_dialognamefile.h"

DialogNameFile::DialogNameFile(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogNameFile)
{
  ui->setupUi(this);
}

DialogNameFile::~DialogNameFile()
{
  delete ui;
}

void DialogNameFile::on_buttonBox_accepted()
{
  emit name_item("f: " + ui->lineEdit->text());
}

