#include "newpersonform.h"
#include "ui_newpersonform.h"

NewPersonForm::NewPersonForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPersonForm)
{
    ui->setupUi(this);
}

NewPersonForm::~NewPersonForm()
{
    delete ui;
}

void NewPersonForm::hideDob()
{
    ui->dateEdit->hide();
    ui->dobLabel->hide();
}

void NewPersonForm::hideDiagnosis()
{
    ui->diagnosisLabel->hide();
    ui->diagnosisLineEdit->hide();
}

