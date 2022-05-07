#ifndef FORMCPPLANGUAGE_H
#define FORMCPPLANGUAGE_H

#include <QWidget>

namespace Ui {
class FormCppLanguage;
}

class FormCppLanguage : public QWidget
{
  Q_OBJECT

public:
  explicit FormCppLanguage(QWidget *parent = nullptr);
  ~FormCppLanguage();

private:
  Ui::FormCppLanguage *ui;
};

#endif // FORMCPPLANGUAGE_H
