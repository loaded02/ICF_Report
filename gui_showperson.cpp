#include "gui_showperson.h"
#include "ui_gui_showperson.h"
#include "gui_newperson.h"
#include <QMessageBox>

void GUI_ShowPerson::fillListView()
{
    ui->listWidget->clear();
    if (art == 'p') {
        for (int i=0; i<icfcontroller->sizeOfPatients(); i++) {
            Patient* actPerson = icfcontroller->getPatient(i);
            new QListWidgetItem(QString::number(actPerson->getId()) + " " + actPerson->getName() + " " + actPerson->getSurname(),ui->listWidget);
        }
    } else if (art == 't') {
        for (int i=0; i<icfcontroller->sizeOfTherapists(); i++) {
            Therapist* actPerson = icfcontroller->getTherapist(i);
            new QListWidgetItem(QString::number(actPerson->getId()) + " " + actPerson->getName() + " " + actPerson->getSurname(),ui->listWidget);
        }
    } else {
        std::cerr << "Art ist weder p noch t" << std::endl;
    }
}

GUI_ShowPerson::GUI_ShowPerson(ICFController *controller, char art, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUI_ShowPerson),icfcontroller(controller),art(art){
    ui->setupUi(this);
    this->fillListView();
    if (art == 'p') {
        connect(ui->newButton,SIGNAL(clicked()),this,SLOT(onActionNew_Patient_clicked()));
    } else if (art == 't') {
        connect(ui->newButton,SIGNAL(clicked()),this,SLOT(onActionNew_Therapist_clicked()));
    } else {
        std::cerr << "Art ist weder p noch t" << std::endl;
    }
}

GUI_ShowPerson::~GUI_ShowPerson()
{
    delete ui;
}

void GUI_ShowPerson::onActionNew_Therapist_clicked()
{
    GUI_NewPerson* therapist = new GUI_NewPerson(this);
    therapist->therapistAppearance();
    therapist->setWindowTitle("Add new Therapist");
    if (therapist->exec())
        this->addTherapist(therapist->getSurname(),therapist->getName(), therapist->getDiagnosis());
    delete therapist;
}

void GUI_ShowPerson::onActionNew_Patient_clicked()
{
    GUI_NewPerson* patient = new GUI_NewPerson(this);
    if (patient->exec())
        this->addPatient(patient->getSurname(),patient->getName(),patient->getDob(),patient->getDiagnosis());
    delete patient;
}

void GUI_ShowPerson::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QStringList stringList = item->text().split(" ");
    GUI_NewPerson* form = new GUI_NewPerson(this);
    if (art == 't') {
        if (Therapist* ther = icfcontroller->findTherapist(stringList[0].toInt())) {
            form->therapistAppearance();
            form->setWindowTitle("Edit Therapist");
            form->setSurname(ther->getSurname());
            form->setName(ther->getName());
            form->setDiagnosis(ther->getCompany());
            if (form->exec()) {
                ther->setSurname(form->getSurname());
                ther->setName(form->getName());
                ther->setCompany(form->getDiagnosis());
            }
        }
    }
    else if (art == 'p') {
        if (Patient* pat = icfcontroller->findPatient(stringList[0].toInt())) {
            form->setSurname(pat->getSurname());
            form->setName(pat->getName());
            form->setDob(pat->getDob());
            form->setDiagnosis(pat->getDiagnosis());
            form->setWindowTitle("Edit Patient");
            if (form->exec()) {
                pat->setSurname(form->getSurname());
                pat->setName(form->getName());
                pat->setDob(form->getDob());
                pat->setDiagnosis(form->getDiagnosis());
            }
        }
    } else {
        std::cerr << "Art ist weder p noch t" << std::endl;
    }
    this->fillListView();
}

void GUI_ShowPerson::on_closeButton_clicked()
{
    this->close();
}

void GUI_ShowPerson::on_editButton_clicked()
{
    QListWidgetItem* item = ui->listWidget->currentItem();
    if (item)
        this->on_listWidget_itemDoubleClicked(item);
}

void GUI_ShowPerson::on_removeButton_clicked()
{
    QListWidgetItem* item = ui->listWidget->currentItem();
    if (item) {
        QStringList stringList = item->text().split(" ");
        switch (art) {
        case 't':
            icfcontroller->removeTherapist(stringList[0].toInt());
            break;
        case 'p':
            icfcontroller->removePatient(stringList[0].toInt());
            break;
        default:std::cerr << "Art ist weder Pat noch Ther" << std::endl;
            break;
        }
        this->fillListView();
    }
}

void GUI_ShowPerson::on_refreshButton_clicked()
{
    this->fillListView();
}

void GUI_ShowPerson::addPatient(QString surname, QString name, QDate dob, QString diagnosis)
{
    Patient* pat = new Patient(surname);
    pat->setName(name);
    pat->setDob(dob);
    pat->setDiagnosis(diagnosis);
    icfcontroller->addPatient(pat);
    emit on_refreshButton_clicked();
}

void GUI_ShowPerson::addTherapist(QString surname, QString name, QString company)
{
    Therapist* ther = new Therapist(surname);
    ther->setName(name);
    ther->setCompany(company);
    icfcontroller->addTherapist(ther);
    emit on_refreshButton_clicked();
}
