#include "formcpplanguage.h"
#include "ui_formcpplanguage.h"

FormCppLanguage::FormCppLanguage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormCppLanguage)
{
  ui->setupUi(this);
}

FormCppLanguage::~FormCppLanguage()
{
  delete ui;
}
