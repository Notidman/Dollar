#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QMdiArea>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

signals:
  void sg_create_menu(QWidget* menu);

private slots:
  void on_pb_templates_clicked();

  void on_pb_projects_clicked();

  void on_pb_settings_clicked();

  void on_pushButton_clicked();

private:
  void create_menu(QWidget* menu);

  Ui::MainWindow* ui;
  QWidget* menu_controller;
};
#endif // MAINWINDOW_H
