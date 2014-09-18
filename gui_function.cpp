#include "gui_function.h"
#include "ui_gui_function.h"

int GUI_Function::NoFunctions = 10;

GUI_Function::GUI_Function(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GUI_Function)
{
    ui->setupUi(this);
}

GUI_Function::~GUI_Function()
{
    delete ui;
}

void GUI_Function::hideUnit(int pos)
{
    switch (pos) {
    case 1:
        ui->widget->resetInput();
        ui->widget->hide();
        break;
    case 2:
        ui->widget_2->resetInput();
        ui->widget_2->hide();
        break;
    case 3:
        ui->widget_3->resetInput();
        ui->widget_3->hide();
        break;
    case 4:
        ui->widget_4->resetInput();
        ui->widget_4->hide();
        break;
    case 5:
        ui->widget_5->resetInput();
        ui->widget_5->hide();
        break;
    case 6:
        ui->widget_6->resetInput();
        ui->widget_6->hide();
        break;
    case 7:
        ui->widget_7->resetInput();
        ui->widget_7->hide();
        break;
    case 8:
        ui->widget_8->resetInput();
        ui->widget_8->hide();
        break;
    case 9:
        ui->widget_9->resetInput();
        ui->widget_9->hide();
        break;
    case 10:
        ui->widget_10->resetInput();
        ui->widget_10->hide();
        break;
    default:
        break;
    }
}

void GUI_Function::hideAll()
{
    for (int i=1; i<=NoFunctions; i++) {
        hideUnit(i);
    }
}

GUI_FunctionForm *GUI_Function::setUnitVisible()
{
    if (ui->widget->isHidden()) {
        ui->widget->setVisible(true);
        return ui->widget;
    }
    else if (ui->widget_2->isHidden()) {
        ui->widget_2->setVisible(true);
        return ui->widget_2;
    }
    else if (ui->widget_3->isHidden()) {
        ui->widget_3->setVisible(true);
        return ui->widget_3;
    }
    else if (ui->widget_4->isHidden()) {
        ui->widget_4->setVisible(true);
        return ui->widget_4;
    }
    else if (ui->widget_5->isHidden()) {
        ui->widget_5->setVisible(true);
        return ui->widget_5;
    }
    else if (ui->widget_6->isHidden()) {
        ui->widget_6->setVisible(true);
        return ui->widget_6;
    }
    else if (ui->widget_7->isHidden()) {
        ui->widget_7->setVisible(true);
        return ui->widget_7;
    }
    else if (ui->widget_8->isHidden()) {
        ui->widget_8->setVisible(true);
        return ui->widget_8;
    }
    else if (ui->widget_9->isHidden()) {
        ui->widget_9->setVisible(true);
        return ui->widget_9;
    }
    else if (ui->widget_10->isHidden()) {
        ui->widget_10->setVisible(true);
        return ui->widget_10;
    }
    else {
        return NULL;
    }
}

void GUI_Function::setLabel(QString text)
{
    ui->label->setText(text);
}

QList<GUI_FunctionForm *> GUI_Function::getActiveWidgets()
{
    QList<GUI_FunctionForm*> list;
    if (ui->widget->isVisible()) {
        list.append(ui->widget);
    }
    if (ui->widget_2->isVisible()) {
        list.append(ui->widget_2);
    }
    if (ui->widget_3->isVisible()) {
        list.append(ui->widget_3);
    }
    if (ui->widget_4->isVisible()) {
        list.append(ui->widget_4);
    }
    if (ui->widget_5->isVisible()) {
        list.append(ui->widget_5);
    }
    if (ui->widget_6->isVisible()) {
        list.append(ui->widget_6);
    }
    if (ui->widget_7->isVisible()) {
        list.append(ui->widget_7);
    }
    if (ui->widget_8->isVisible()) {
        list.append(ui->widget_8);
    }
    if (ui->widget_9->isVisible()) {
        list.append(ui->widget_9);
    }
    if (ui->widget_10->isVisible()) {
        list.append(ui->widget_10);
    }
    return list;
}

void GUI_Function::on_addButton_clicked()
{
    this->setUnitVisible();
}

void GUI_Function::on_removeButton_clicked()
{
    if (ui->widget->isChecked()) {
        hideUnit(1);
    }
    if (ui->widget_2->isChecked()) {
        hideUnit(2);
    }
    if (ui->widget_3->isChecked()) {
        hideUnit(3);
    }
    if (ui->widget_4->isChecked()) {
        hideUnit(4);
    }
    if (ui->widget_5->isChecked()) {
        hideUnit(5);
    }
    if (ui->widget_6->isChecked()) {
        hideUnit(6);
    }
    if (ui->widget_7->isChecked()) {
        hideUnit(7);
    }
    if (ui->widget_8->isChecked()) {
        hideUnit(8);
    }
    if (ui->widget_9->isChecked()) {
        hideUnit(9);
    }
    if (ui->widget_10->isChecked()) {
        hideUnit(10);
    }
}
