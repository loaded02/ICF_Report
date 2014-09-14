#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ICF Report");
    //show 3 forms at startup
    for (int i = 4; i < 11; ++i) {
        ui->functionsWidget->hideUnit(i);
        ui->structuresWidget->hideUnit(i);
        ui->partizipationWidget->hideUnit(i);
        ui->contextWidget->hideUnit(i);
    }
    ui->structuresWidget->setLabel("Bodystructures");
    ui->partizipationWidget->setLabel("Participation");
    ui->contextWidget->setLabel("Context Factors");
    icfController = new ICFController();
    this->fillTherComboBox();
    this->fillPatComboBox();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete icfController;
}

void MainWindow::on_cancelButton_clicked()
{
    this->close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"About ICF Report", "ICF Report is used to easily create short ICF Reports. It also includes a simple"
                       " patient management system.\nCreated by loaded 2014");
}

void MainWindow::on_actionNew_Therapist_triggered()
{
//    QString therapist = QInputDialog::getText(this, "Enter Therapist Name", QString::null,QLineEdit::Normal,"Enter Therapist Name");
//    ui->therapeutcB->addItem(therapist);
    GUI_NewPerson* therapist = new GUI_NewPerson(this);
    therapist->therapistAppearance();
    therapist->setWindowTitle("Add new Therapist");
    if (therapist->exec())
        this->addTherapist(therapist->getSurname(),therapist->getName());
}

void MainWindow::on_actionNew_Patient_triggered()
{
    GUI_NewPerson* patient = new GUI_NewPerson(this);
    if (patient->exec())
        this->addPatient(patient->getSurname(),patient->getName(),patient->getDob(),patient->getDiagnosis());
}

void MainWindow::on_saveButton_clicked()
{
    icfController->save();
}

void MainWindow::fillTherComboBox()
{
    ui->therapeutcB->clear();
    for (int i=0; i<icfController->sizeOfTherapists(); i++) {
        ui->therapeutcB->addItem(icfController->getTherapist(i)->getSurname());
    }
}

void MainWindow::fillPatComboBox()
{
    ui->patientcB->clear();
    for (int i=0; i<icfController->sizeOfPatients(); i++) {
        ui->patientcB->addItem(icfController->getPatient(i)->getSurname());
    }
}

void MainWindow::addPatient(QString surname, QString name, QDate dob, QString diagnosis)
{
    Patient* pat = new Patient(surname);
    pat->setName(name);
    pat->setDob(dob);
    pat->setDiagnosis(diagnosis);
    icfController->addPatient(pat);
    this->fillPatComboBox();
}

void MainWindow::addTherapist(QString surname, QString name)
{
    Therapist* ther = new Therapist(surname);
    ther->setName(name);
    icfController->addTherapist(ther);
    this->fillTherComboBox();
}

void MainWindow::on_printButton_clicked()
{
    icfController->printReport();
}

void MainWindow::on_actionManage_Therapists_triggered()
{
    GUI_ShowPerson* form = new GUI_ShowPerson(icfController->getTherapists(),this);
    form->setWindowTitle("Manage Therapists");
    form->exec();
}

void MainWindow::on_actionManage_Patients_triggered()
{
    GUI_ShowPerson* form = new GUI_ShowPerson(icfController->getPatients(),this);
    form->setWindowTitle("Manage Patients");
    form->exec();
}
