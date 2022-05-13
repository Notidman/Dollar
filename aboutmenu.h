#ifndef ABOUTMENU_H
#define ABOUTMENU_H

#include <QWidget>
#include "welcomemenu.h"

namespace Ui {
class AboutMenu;
}

class AboutMenu : public QWidget
{
  Q_OBJECT

public:
  explicit AboutMenu(QWidget *parent = nullptr);
  ~AboutMenu();

private:
  Welcomemenu* welcome_menu;
  Ui::AboutMenu *ui;
};

#endif // ABOUTMENU_H
