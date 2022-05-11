#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <QWidget>

namespace Ui {
class SettingsMenu;
}

class SettingsMenu : public QWidget
{
  Q_OBJECT

public:
  explicit SettingsMenu(QWidget *parent = nullptr);
  ~SettingsMenu();

signals:
  void set_theme(const QString& str);

private slots:
  void on_comboBox_2_activated(const QString &arg1);

private:
  Ui::SettingsMenu *ui;
};

#endif // SETTINGSMENU_H
