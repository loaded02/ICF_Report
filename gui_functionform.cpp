#include "gui_functionform.h"
#include "ui_gui_functionform.h"

GUI_FunctionForm::GUI_FunctionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GUI_FunctionForm)
{
    ui->setupUi(this);
    ui->comboBox->addItems(QStringList() << "ID 12" << "ID 13" << "ID 14");
}

GUI_FunctionForm::~GUI_FunctionForm()
{
    delete ui;
}

void GUI_FunctionForm::setDescription(QString text)
{
    ui->label->setText(text);
}

bool GUI_FunctionForm::isChecked()
{
    return ui->checkBox->isChecked();
}

int GUI_FunctionForm::getValue()
{
    if (ui->radioButton->isChecked())
        return 0;
    if (ui->radioButton_2->isChecked())
        return 1;
    if (ui->radioButton_3->isChecked())
        return 2;
    if (ui->radioButton_4->isChecked())
        return 3;
    if (ui->radioButton_5->isChecked())
        return 4;
    else return -1;
}

void GUI_FunctionForm::setValue(int val)
{
    switch (val) {
    case 0 : ui->radioButton->setChecked(true);
        break;
    case 1 : ui->radioButton_2->setChecked(true);
        break;
    case 2 : ui->radioButton_3->setChecked(true);
        break;
    case 3 : ui->radioButton_4->setChecked(true);
        break;
    case 4 : ui->radioButton_5->setChecked(true);
        break;
    default: ;
    }
}

QString GUI_FunctionForm::getDescription()
{
    return ui->label->text();
}

QString GUI_FunctionForm::getId()
{
    return ui->comboBox->currentText();
}

void GUI_FunctionForm::setId(QString id)
{
    int i;
    if ((i= ui->comboBox->findText(id)) >= 0) {
        ui->comboBox->setCurrentIndex(i);
    } else {
        ui->comboBox->addItem(id);
    }
}

QString GUI_FunctionForm::getText()
{
    return ui->lineEdit->text();
}

void GUI_FunctionForm::setText(QString txt)
{
    ui->lineEdit->setText(txt);
}
