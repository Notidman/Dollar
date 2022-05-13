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
  DollarWriter* dollar_writer;
  Ui::ProjectsMenu *ui;
};

#endif // PROJECTSMENU_H
