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
  ~FormPhpLanguage();

private:
  Ui::FormPhpLanguage *ui;
};

#endif // FORMPHPLANGUAGE_H
