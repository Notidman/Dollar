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
  return ui->comboBox_build_system->placeholderText();
}

QStringList FormCppLanguage::list_libs()
{
  QStringList libs;
  if (ui->cb_opencv->isEnabled())
    libs.append("OpenCv");
  if (ui->cb_sdl->isEnabled())
    libs.append("SDL");
  if (ui->cb_sfml->isEnabled())
    libs.append("SFML");

  return libs;
}

FormCppLanguage::~FormCppLanguage()
{
  delete ui;
}
