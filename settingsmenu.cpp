#include "settingsmenu.h"
#include "ui_settingsmenu.h"

SettingsMenu::SettingsMenu(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SettingsMenu)
{
  ui->setupUi(this);
}

SettingsMenu::~SettingsMenu()
{
  delete ui;
}
