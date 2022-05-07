#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  templates_menu = new TemplatesMenu();
  projects_menu = new ProjectsMenu();
  settings_menu = new SettingsMenu();
  git_menu = new GitMenu();

  ui->gl_templates_menu->addWidget(templates_menu);
  ui->gl_projects_menu->addWidget(projects_menu);
  ui->gl_settings_menu->addWidget(settings_menu);
  ui->gl_git_menu->addWidget(git_menu);

  connect(settings_menu, &SettingsMenu::set_theme, this, &MainWindow::set_theme);
}

MainWindow::~MainWindow()
{
  delete ui;
  delete templates_menu;
  delete projects_menu;
  delete settings_menu;
  delete git_menu;
}

void MainWindow::set_theme(QString name_theme)
{
  if ( name_theme == "Gray")
  {
    setStyleSheet("background-color: gray;");
  }

  if ( name_theme == "Light")
  {
    setStyleSheet("");
  }
}
