#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->gl_templates_menu->addWidget(new TemplatesMenu());
  ui->gl_projects_menu->addWidget(new ProjectsMenu());
  ui->gl_settings_menu->addWidget(new SettingsMenu());
}

MainWindow::~MainWindow()
{
  delete ui;
}
