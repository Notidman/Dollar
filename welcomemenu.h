#ifndef WELCOMEMENU_H
#define WELCOMEMENU_H

#include <QWidget>

namespace Ui {
class Welcomemenu;
}

class Welcomemenu : public QWidget
{
  Q_OBJECT

public:
  explicit Welcomemenu(QWidget *parent = nullptr);
  ~Welcomemenu();

private:
  Ui::Welcomemenu *ui;
};

#endif // WELCOMEMENU_H
