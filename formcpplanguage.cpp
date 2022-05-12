#include "formcpplanguage.h"
#include "ui_formcpplanguage.h"

FormCppLanguage::FormCppLanguage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormCppLanguage)
{
  ui->setupUi(this);
}

void FormCppLanguage::set_build_system(const QString& str)
{
  if ( str == "None")
    ui->comboBox_build_system->setCurrentIndex(0);
  else if ( str == "Make")
    ui->comboBox_build_system->setCurrentIndex(1);
  else if ( str == "CMake")
    ui->comboBox_build_system->setCurrentIndex(2);
}

void FormCppLanguage::set_list_libs(const QStringList& str)
{
  for(auto& lib:str)
  {
    if ( lib == "OpenCv")
      ui->cb_opencv->setChecked(true);
    if ( lib == "SDL")
      ui->cb_sdl->setChecked(true);
    if ( lib == "SFML")
      ui->cb_sfml->setChecked(true);
  }
}

QString FormCppLanguage::build_system()
{
  return ui->comboBox_build_system->currentText();
}

QStringList FormCppLanguage::list_libs()
{
  QStringList libs;
  if (ui->cb_opencv->isChecked())
    libs.append("OpenCv");
  if (ui->cb_sdl->isChecked())
    libs.append("SDL");
  if (ui->cb_sfml->isChecked())
    libs.append("SFML");

  return libs;
}

FormCppLanguage::~FormCppLanguage()
{
  delete ui;
}
