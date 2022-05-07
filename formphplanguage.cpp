#include "formphplanguage.h"
#include "ui_formphplanguage.h"

FormPhpLanguage::FormPhpLanguage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormPhpLanguage)
{
  ui->setupUi(this);
}

FormPhpLanguage::~FormPhpLanguage()
{
  delete ui;
}
