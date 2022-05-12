#include "formtemplate.h"
#include "ui_formtemplate.h"

FormTemplate::FormTemplate(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormTemplate)
{
  ui->setupUi(this);
}

FormTemplate::~FormTemplate()
{
  delete ui;
}
