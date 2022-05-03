#ifndef PROJECTSMENU_H
#define PROJECTSMENU_H

#include <QWidget>

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
  void on_pushButton_3_clicked();

private:
  Ui::ProjectsMenu *ui;
};

#endif // PROJECTSMENU_H
