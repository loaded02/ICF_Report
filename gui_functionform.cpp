#include "gui_functionform.h"
#include "ui_gui_functionform.h"
#include <QDebug>
#include <QInputDialog>
#include <stdlib.h>
#include <time.h>

GUI_FunctionForm::GUI_FunctionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GUI_FunctionForm)
{
    ui->setupUi(this);
    srand(time(NULL));

    ui->radioButton_6->hide();
    ui->radioButton_7->hide();
    ui->radioButton_8->hide();
    ui->radioButton_9->hide();
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
    if (ui->radioButton_6->isChecked())
        return 5;
    if (ui->radioButton_7->isChecked())
        return 6;
    if (ui->radioButton_8->isChecked())
        return 7;
    if (ui->radioButton_9->isChecked())
        return 8;
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
    case 5 : ui->radioButton_6->setChecked(true);
        break;
    case 6 : ui->radioButton_7->setChecked(true);
        break;
    case 7 : ui->radioButton_8->setChecked(true);
        break;
    case 8 : ui->radioButton_9->setChecked(true);
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
    if ((i= ui->comboBox->findText(id)) == -1) {
        ui->comboBox->addItem(id);
        i= ui->comboBox->findText(id);
    }
    if (ui->comboBox->currentIndex() == i) {
        this->on_comboBox_currentIndexChanged(id);
    } else {
        ui->comboBox->setCurrentIndex(i);
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

void GUI_FunctionForm::resetInput()
{
    ui->checkBox->setChecked(false);
    ui->comboBox->setCurrentIndex(0);
    ui->label->setText("Description");
    ui->lineEdit->clear();
    int btn = this->getValue();
    if (btn != -1) {
        QRadioButton* selectedBtn = 0;
        switch (btn) {
        case 0 : selectedBtn = ui->radioButton;
            break;
        case 1 : selectedBtn = ui->radioButton_2;
            break;
        case 2 : selectedBtn = ui->radioButton_3;
            break;
        case 3 : selectedBtn = ui->radioButton_4;
            break;
        case 4 : selectedBtn = ui->radioButton_5;
            break;
        case 5 : selectedBtn = ui->radioButton_6;
            break;
        case 6 : selectedBtn = ui->radioButton_7;
            break;
        case 7 : selectedBtn = ui->radioButton_8;
            break;
        case 8 : selectedBtn = ui->radioButton_9;
            break;
        default :;
        }
        if (selectedBtn) {
            selectedBtn->setAutoExclusive(false);
            selectedBtn->setChecked(false);
            selectedBtn->setAutoExclusive(true);
        }
    }
}

void GUI_FunctionForm::showContextRadio()
{
    ui->radioButton_6->show();
    ui->radioButton_7->show();
    ui->radioButton_8->show();
    ui->radioButton_9->show();
}

void GUI_FunctionForm::changeDescription(const QString &arg1, int rnd)
{
    if (this->rnd == rnd)
        ui->label->setText(arg1);
}

void GUI_FunctionForm::addIcfCodeToCb(const QString &arg1)
{
    ui->comboBox->addItem(arg1);
}

void GUI_FunctionForm::on_comboBox_currentIndexChanged(const QString &arg1)
{
    rnd = rand();
    emit idChanged(arg1, rnd);
}
