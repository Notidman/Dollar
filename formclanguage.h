#ifndef FORMCLANGUAGE_H
#define FORMCLANGUAGE_H

#include <QWidget>

namespace Ui {
class FormCLanguage;
}

class FormCLanguage : public QWidget
{
  Q_OBJECT

public:
  explicit FormCLanguage(QWidget *parent = nullptr);
  void set_build_system(const QString &str);
  void set_list_libs(const QStringList &str);
  QString build_system();
  QStringList list_libs();
  ~FormCLanguage();

private:
  Ui::FormCLanguage *ui;
};

#endif // FORMCLANGUAGE_H
