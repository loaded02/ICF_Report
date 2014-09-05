#include "functionform.h"
#include "ui_functionform.h"

FunctionForm::FunctionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionForm)
{
    ui->setupUi(this);
    ui->comboBox->addItems(QStringList() << "ID 12" << "ID 13" << "ID 14");
}

FunctionForm::~FunctionForm()
{
    delete ui;
}

void FunctionForm::setLabel(QString text)
{
    ui->label->setText(text);
}

bool FunctionForm::isChecked()
{
    return ui->checkBox->isChecked();
}

int FunctionForm::getValue()
{
    if (ui->radioButton->isChecked())
        return 0;
    else if (ui->radioButton_2->isChecked())
        return 1;
    else if (ui->radioButton_3->isChecked())
        return 2;
    else if (ui->radioButton_4->isChecked())
        return 3;
    else if (ui->radioButton_5->isChecked())
        return 4;
}

QString FunctionForm::getDescription()
{
    return ui->lineEdit->text();
}

void FunctionForm::on_comboBox_currentIndexChanged(const QString &arg1)
{

}
