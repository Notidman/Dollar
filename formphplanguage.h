#ifndef FORMPHPLANGUAGE_H
#define FORMPHPLANGUAGE_H

#include <QWidget>

namespace Ui {
class FormPhpLanguage;
}

class FormPhpLanguage : public QWidget
{
  Q_OBJECT

public:
  explicit FormPhpLanguage(QWidget *parent = nullptr);
  QStringList list_libs();
  void set_list_libs(const QStringList &str);
  ~FormPhpLanguage();

private:
  Ui::FormPhpLanguage *ui;
};

#endif // FORMPHPLANGUAGE_H
