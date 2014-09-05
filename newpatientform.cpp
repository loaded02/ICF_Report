#include "newpatientform.h"
#include "ui_newpatientform.h"

NewPatientForm::NewPatientForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPatientForm)
{
    ui->setupUi(this);
}

NewPatientForm::~NewPatientForm()
{
    delete ui;
}
