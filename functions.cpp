#include "functions.h"
#include "ui_functions.h"

Functions::Functions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Functions)
{
    ui->setupUi(this);
}

Functions::~Functions()
{
    delete ui;
}

void Functions::hideUnit(int pos)
{
    switch (pos) {
    case 1:
        ui->widget->hide();
        break;
    case 2:
        ui->widget_2->hide();
        break;
    case 3:
        ui->widget_3->hide();
        break;
    case 4:
        ui->widget_4->hide();
        break;
    case 5:
        ui->widget_5->hide();
        break;
    case 6:
        ui->widget_6->hide();
        break;
    case 7:
        ui->widget_7->hide();
        break;
    case 8:
        ui->widget_8->hide();
        break;
    case 9:
        ui->widget_9->hide();
        break;
    case 10:
        ui->widget_10->hide();
        break;
    default:
        break;
    }
}

void Functions::setLabel(QString text)
{
    ui->label->setText(text);
}

void Functions::on_addButton_clicked()
{
    if (ui->widget->isHidden()) {
        ui->widget->setVisible(true);
    }
    else if (ui->widget_2->isHidden()) {
        ui->widget_2->setVisible(true);
    }
    else if (ui->widget_3->isHidden()) {
        ui->widget_3->setVisible(true);
    }else if (ui->widget_4->isHidden()) {
        ui->widget_4->setVisible(true);
    }else if (ui->widget_5->isHidden()) {
        ui->widget_5->setVisible(true);
    }else if (ui->widget_6->isHidden()) {
        ui->widget_6->setVisible(true);
    }else if (ui->widget_7->isHidden()) {
        ui->widget_7->setVisible(true);
    }else if (ui->widget_8->isHidden()) {
        ui->widget_8->setVisible(true);
    }else if (ui->widget_9->isHidden()) {
        ui->widget_9->setVisible(true);
    }else if (ui->widget_10->isHidden()) {
        ui->widget_10->setVisible(true);
    }
}

void Functions::on_removeButton_clicked()
{
    if (ui->widget->isChecked()) {
        ui->widget->setVisible(false);
    }
    if (ui->widget_2->isChecked()) {
        ui->widget_2->setVisible(false);
    }
    if (ui->widget_3->isChecked()) {
        ui->widget_3->setVisible(false);
    }
    if (ui->widget_4->isChecked()) {
        ui->widget_4->setVisible(false);
    }
    if (ui->widget_5->isChecked()) {
        ui->widget_5->setVisible(false);
    }
    if (ui->widget_6->isChecked()) {
        ui->widget_6->setVisible(false);
    }
    if (ui->widget_7->isChecked()) {
        ui->widget_7->setVisible(false);
    }
    if (ui->widget_8->isChecked()) {
        ui->widget_8->setVisible(false);
    }
    if (ui->widget_9->isChecked()) {
        ui->widget_9->setVisible(false);
    }
    if (ui->widget_10->isChecked()) {
        ui->widget_10->setVisible(false);
    }
}
