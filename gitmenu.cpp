#include "gitmenu.h"
#include "ui_gitmenu.h"

GitMenu::GitMenu(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GitMenu)
{
  ui->setupUi(this);
}

GitMenu::~GitMenu()
{
  delete ui;
}
