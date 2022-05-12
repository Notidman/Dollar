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
  if (ui->cb_laravel->isChecked())
    libs.append("Laravel");
  if (ui->cb_symfony->isChecked())
    libs.append("Symfony");

  return libs;
}

void FormPhpLanguage::set_list_libs(const QStringList &str)
{
  for(auto& lib:str)
  {
    if ( lib == "Laravel")
      ui->cb_laravel->setChecked(true);
    if ( lib == "Symfony")
      ui->cb_symfony->setChecked(true);
  }
}

FormPhpLanguage::~FormPhpLanguage()
{
  delete ui;
}
