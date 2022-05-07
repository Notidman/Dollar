#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>

#include "templatesmenu.h"
#include "settingsmenu.h"
#include "projectsmenu.h"
#include "gitmenu.h"
#include "welcomemenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

public slots:
  void set_theme(QString name_theme);

private:
  Ui::MainWindow* ui;
  GitMenu* git_menu;
  TemplatesMenu* templates_menu;
  SettingsMenu* settings_menu;
  ProjectsMenu* projects_menu;
};
#endif // MAINWINDOW_H
