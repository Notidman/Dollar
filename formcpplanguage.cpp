#include "formcpplanguage.h"
#include "ui_formcpplanguage.h"

FormCppLanguage::FormCppLanguage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormCppLanguage)
{
  ui->setupUi(this);
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
