#include "gui_newperson.h"
#include "ui_gui_newperson.h"

GUI_NewPerson::GUI_NewPerson(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUI_NewPerson)
{
    ui->setupUi(this);
}

GUI_NewPerson::~GUI_NewPerson()
{
    delete ui;
}

void GUI_NewPerson::therapistAppearance()
{
    //this->hideDiagnosis();
    ui->diagnosisLabel->setText("Company");
    this->hideDob();
}

void GUI_NewPerson::hideDob()
{
    ui->dateEdit->hide();
    ui->dobLabel->hide();
}

void GUI_NewPerson::hideDiagnosis()
{
    ui->diagnosisLabel->hide();
    ui->diagnosisLineEdit->hide();
}

void GUI_NewPerson::setSurname(QString surname)
{
    ui->surnameLineEdit->setText(surname);
}

QString GUI_NewPerson::getSurname()
{
    return ui->surnameLineEdit->text();
}

void GUI_NewPerson::setName(QString name)
{
    ui->nameLineEdit->setText(name);
}

QString GUI_NewPerson::getName()
{
    return ui->nameLineEdit->text();
}

void GUI_NewPerson::setDob(QDate dob)
{
    ui->dateEdit->setDate(dob);
}

QDate GUI_NewPerson::getDob()
{
    return ui->dateEdit->date();
}

void GUI_NewPerson::setDiagnosis(QString diagnosis)
{
    ui->diagnosisLineEdit->setText(diagnosis);
}

QString GUI_NewPerson::getDiagnosis()
{
    return ui->diagnosisLineEdit->text();
}

