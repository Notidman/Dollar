#include "formphplanguage.h"
#include "ui_formphplanguage.h"

FormPhpLanguage::FormPhpLanguage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormPhpLanguage)
{
  ui->setupUi(this);
}

QStringList FormPhpLanguage::list_libs()
{
  QStringList libs;
  if (ui->cb_laravel->isEnabled())
    libs.append("Laravel");
  if (ui->cb_symfony->isEnabled())
    libs.append("Symfony");

  return libs;
}

FormPhpLanguage::~FormPhpLanguage()
{
  delete ui;
}
