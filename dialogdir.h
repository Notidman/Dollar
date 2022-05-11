#ifndef DIALOGDIR_H
#define DIALOGDIR_H

#include <QDialog>

namespace Ui {
class DialogNameDir;
}

class DialogDir : public QDialog
{
  Q_OBJECT

public:
  explicit DialogDir(QWidget *parent = nullptr);
  ~DialogDir();

signals:
  void dir_info(const QString& str);

public slots:
  void set_dir_name(const QString& str);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::DialogNameDir *ui;
};

#endif // DIALOGDIR_H
