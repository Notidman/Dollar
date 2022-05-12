#ifndef FORMTEMPLATE_H
#define FORMTEMPLATE_H

#include <QWidget>

namespace Ui {
class FormTemplate;
}

class FormTemplate : public QWidget
{
  Q_OBJECT

public:
  explicit FormTemplate(QWidget *parent = nullptr);
  ~FormTemplate();

private:
  Ui::FormTemplate *ui;
};

#endif // FORMTEMPLATE_H
