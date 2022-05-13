#include "aboutmenu.h"
#include "ui_aboutmenu.h"

AboutMenu::AboutMenu(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AboutMenu)
{
  ui->setupUi(this);

  welcome_menu = new Welcomemenu(this);
  ui->gridLayout_welcome_menu->addWidget(welcome_menu);
  ui->lb_qt_version_info->setText(qVersion());
  ui->lb_author_info->setText("Notidman");
  ui->lb_program_version_info->setText("0.1");
  ui->lb_contact_developer_info->setText("ognieff@yandex.ru");
}

AboutMenu::~AboutMenu()
{
  delete ui;
  delete welcome_menu;
}
