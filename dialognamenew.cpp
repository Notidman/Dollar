#include "dialognamenew.h"
#include "ui_dialognamenew.h"

DialogNameNew::DialogNameNew(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogNameNew)
{
  ui->setupUi(this);
}

DialogNameNew::~DialogNameNew()
{
  delete ui;
}

void DialogNameNew::on_buttonBox_accepted()
{
  emit name_item(ui->lineEdit->text());
}

