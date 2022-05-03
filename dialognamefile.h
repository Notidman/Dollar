#ifndef DIALOGNAMEFILE_H
#define DIALOGNAMEFILE_H

#include <QDialog>

namespace Ui {
class DialogNameFile;
}

class DialogNameFile : public QDialog
{
  Q_OBJECT

public:
  explicit DialogNameFile(QWidget *parent = nullptr);
  ~DialogNameFile();

signals:
  void name_item(QString str);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::DialogNameFile *ui;
};

#endif // DIALOGNAMEFILE_H
