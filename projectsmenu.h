#ifndef PROJECTSMENU_H
#define PROJECTSMENU_H

#include <QWidget>
#include "dollarwriter.h"

namespace Ui {
class ProjectsMenu;
}

class ProjectsMenu : public QWidget
{
  Q_OBJECT

public:
  explicit ProjectsMenu(QWidget *parent = nullptr);
  ~ProjectsMenu();

private slots:
  void on_pb_reset_clicked();

  void on_pb_select_template_clicked();

  void on_pb_select_path_clicked();

  void on_pb_create_clicked();

private:
  void create_project_struct(const QJsonArray &array, const QString &path);
  void create_project_element(const QJsonObject &json, const QString &path);
  void gen_make(const QString& path);
  void gen_cmake(const QString& path);

private:
  DollarWriter* dollar_writer;
  Ui::ProjectsMenu *ui;
};

#endif // PROJECTSMENU_H
