#ifndef GITMENU_H
#define GITMENU_H

#include <QWidget>

namespace Ui {
class GitMenu;
}

class GitMenu : public QWidget
{
  Q_OBJECT

public:
  explicit GitMenu(QWidget *parent = nullptr);
  ~GitMenu();

private:
  Ui::GitMenu *ui;
};

#endif // GITMENU_H
