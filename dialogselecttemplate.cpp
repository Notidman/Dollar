#include "dialogselecttemplate.h"
#include "ui_dialogselecttemplate.h"

DialogSelectTemplate::DialogSelectTemplate(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogSelectTemplate)
{
  ui->setupUi(this);
}

DialogSelectTemplate::~DialogSelectTemplate()
{
  delete ui;
}
