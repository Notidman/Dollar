#ifndef DIALOGNAMENEW_H
#define DIALOGNAMENEW_H

#include <QDialog>

namespace Ui {
class DialogNameNew;
}

class DialogNameNew : public QDialog
{
  Q_OBJECT

public:
  explicit DialogNameNew(QWidget *parent = nullptr);
  ~DialogNameNew();

private slots:
  void on_buttonBox_accepted();

signals:
  void name_item(QString str);

private:
  Ui::DialogNameNew *ui;
};

#endif // DIALOGNAMENEW_H
