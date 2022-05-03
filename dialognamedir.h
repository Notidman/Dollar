#ifndef DIALOGNAMEDIR_H
#define DIALOGNAMEDIR_H

#include <QDialog>

namespace Ui {
class DialogNameDir;
}

class DialogNameDir : public QDialog
{
  Q_OBJECT

public:
  explicit DialogNameDir(QWidget *parent = nullptr);
  ~DialogNameDir();

signals:
  void name_item(QString str);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::DialogNameDir *ui;
};

#endif // DIALOGNAMEDIR_H
