#include "formclanguage.h"
#include "ui_formclanguage.h"

FormCLanguage::FormCLanguage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormCLanguage)
{
  ui->setupUi(this);
}

void FormCLanguage::set_build_system(const QString &str)
{
  if ( str == "None")
    ui->comboBox_build_system->setCurrentIndex(0);
//  else if ( str == "Make")
//    ui->comboBox_build_system->setCurrentIndex(1);
  else if ( str == "CMake")
    ui->comboBox_build_system->setCurrentIndex(1);
}

void FormCLanguage::set_list_libs(const QStringList &str)
{
  for(auto& lib:str)
  {
    if ( lib == "libgit2")
      ui->cb_libgit2->setChecked(true);
    if ( lib == "libzip")
      ui->cb_libzip->setChecked(true);
  }
}

QString FormCLanguage::build_system()
{
  return ui->comboBox_build_system->currentText();
}

QStringList FormCLanguage::list_libs()
{
  QStringList libs;
  if ( ui->cb_libgit2->isChecked())
    libs.append("libgit2");
  if ( ui->cb_libzip->isChecked())
    libs.append("libzip");

  return libs;
}

FormCLanguage::~FormCLanguage()
{
  delete ui;
}
