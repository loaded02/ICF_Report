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
