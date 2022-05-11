#include "dialognamenew.h"
#include "ui_dialognamenew.h"
#include <QMessageBox>

DialogNameNew::DialogNameNew(QWidget *parent, QString old_name) :
  QDialog(parent),
  ui(new Ui::DialogNameNew)
{
  ui->setupUi(this);
  ui->lineEdit->setText(old_name);
}

DialogNameNew::~DialogNameNew()
{
  delete ui;
}

void DialogNameNew::on_buttonBox_accepted()
{
  if( ui->lineEdit->text() == "" )
  {
    QMessageBox::critical(this, "Error", "The file cannot be without a name!");
    return;
  }

  emit info_dialog(ui->lineEdit->text());
}

