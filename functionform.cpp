#include "functionform.h"
#include "ui_functionform.h"

FunctionForm::FunctionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionForm)
{
    ui->setupUi(this);
}

FunctionForm::~FunctionForm()
{
    delete ui;
}

void FunctionForm::setLabel(QString text)
{
    ui->label->setText(text);
}
