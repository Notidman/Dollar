#ifndef DIALOGSELECTTEMPLATE_H
#define DIALOGSELECTTEMPLATE_H

#include <QDialog>

namespace Ui {
class DialogSelectTemplate;
}

class DialogSelectTemplate : public QDialog
{
  Q_OBJECT

public:
  explicit DialogSelectTemplate(QWidget *parent = nullptr);
  ~DialogSelectTemplate();

private:
  Ui::DialogSelectTemplate *ui;
};

#endif // DIALOGSELECTTEMPLATE_H
