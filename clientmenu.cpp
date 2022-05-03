#include "clientmenu.h"
#include "ui_clientmenu.h"

ClientMenu::ClientMenu(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ClientMenu)
{
  ui->setupUi(this);
}

ClientMenu::~ClientMenu()
{
  delete ui;
}
