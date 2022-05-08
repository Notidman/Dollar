#ifndef DIALOGWRITEINFILE_H
#define DIALOGWRITEINFILE_H

#include <QDialog>

namespace Ui {
class DialogWriteInFile;
}

class DialogWriteInFile : public QDialog
{
  Q_OBJECT

public:
  explicit DialogWriteInFile(QWidget *parent = nullptr);
  ~DialogWriteInFile();

private slots:
  void on_buttonBox_accepted();

private:
  Ui::DialogWriteInFile *ui;
};

#endif // DIALOGWRITEINFILE_H
