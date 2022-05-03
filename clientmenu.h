#ifndef CLIENTMENU_H
#define CLIENTMENU_H

#include <QWidget>

namespace Ui {
class ClientMenu;
}

class ClientMenu : public QWidget
{
  Q_OBJECT

public:
  explicit ClientMenu(QWidget *parent = nullptr);
  ~ClientMenu();

private:
  Ui::ClientMenu *ui;
};

#endif // CLIENTMENU_H
