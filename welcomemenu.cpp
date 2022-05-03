#include "welcomemenu.h"
#include "ui_welcomemenu.h"

Welcomemenu::Welcomemenu(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Welcomemenu)
{
  ui->setupUi(this);
}

Welcomemenu::~Welcomemenu()
{
  delete ui;
}
