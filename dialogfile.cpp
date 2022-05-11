#include "dialogfile.h"
#include "ui_dialogfile.h"

DialogFile::DialogFile(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogNameFile)
{
  ui->setupUi(this);
}

DialogFile::~DialogFile()
{
  delete ui;
}

void DialogFile::set_file_name(const QString &str)
{
  ui->lineEdit->setText(str);
}

void DialogFile::set_file_content(const QString &str)
{
  ui->textEdit_content_file->setText(str);
}

void DialogFile::on_buttonBox_accepted()
{
  QStringList list;
  list << ui->lineEdit->text() << ui->textEdit_content_file->toPlainText();
  emit file_info(list);
}

