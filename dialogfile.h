#ifndef DIALOGFILE_H
#define DIALOGFILE_H

#include <QDialog>

namespace Ui {
class DialogNameFile;
}

class DialogFile : public QDialog
{
  Q_OBJECT

public:
  explicit DialogFile(QWidget *parent = nullptr);
  ~DialogFile();

signals:
  void file_info(const QStringList& str);

public slots:
  void set_file_name(const QString& str);
  void set_file_content(const QString& str);
private slots:
  void on_buttonBox_accepted();

private:
  Ui::DialogNameFile *ui;
};

#endif // DIALOGFILE_H
