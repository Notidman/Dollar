#ifndef ABOUTMENU_H
#define ABOUTMENU_H

#include <QWidget>

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
  Ui::AboutMenu *ui;
};

#endif // ABOUTMENU_H
