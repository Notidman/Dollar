#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "templatesmenu.h"
#include "settingsmenu.h"
#include "projectsmenu.h"
#include "welcomemenu.h"
#include "clientmenu.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  menu_controller = nullptr;

  create_menu(new Welcomemenu());
}

MainWindow::~MainWindow()
{
  delete ui;
  delete menu_controller;
}

void MainWindow::create_menu(QWidget* menu)
{
  if ( menu_controller != nullptr ) { delete menu_controller; }
  menu_controller = menu;
  ui->menu_panel->addWidget(menu_controller);
}

void MainWindow::on_pb_templates_clicked()
{
  create_menu(new TemplatesMenu());
}


void MainWindow::on_pb_projects_clicked()
{
  create_menu(new ProjectsMenu());
}

void MainWindow::on_pb_settings_clicked()
{
  create_menu(new SettingsMenu());
}


void MainWindow::on_pushButton_clicked()
{
  create_menu(new ClientMenu());
}

