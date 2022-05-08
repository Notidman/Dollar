#include "dialogwriteinfile.h"
#include "ui_dialogwriteinfile.h"

DialogWriteInFile::DialogWriteInFile(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogWriteInFile)
{
  ui->setupUi(this);
}

DialogWriteInFile::~DialogWriteInFile()
{
  delete ui;
}

void DialogWriteInFile::on_buttonBox_accepted()
{
}

