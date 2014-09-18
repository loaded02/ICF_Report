#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),currentReportId(0)
{
    ui->setupUi(this);
    this->setWindowTitle("ICF Report");
    ui->structuresWidget->setLabel("Bodystructures");
    ui->partizipationWidget->setLabel("Participation");
    ui->contextWidget->setLabel("Context Factors");
    icfController = new ICFController();
    this->fillTherComboBox();
    this->fillPatComboBox();
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionPrint_Pdf,SIGNAL(triggered()),this,SLOT(on_printButton_clicked()));
    connect(ui->actionSave_Report,SIGNAL(triggered()),this,SLOT(on_saveButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete icfController;
}

void MainWindow::on_cancelButton_clicked()
{
    ui->reportcB->setCurrentIndex(0);
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
    delete therapist;
}

void MainWindow::on_actionNew_Patient_triggered()
{
    GUI_NewPerson* patient = new GUI_NewPerson(this);
    if (patient->exec())
        this->addPatient(patient->getSurname(),patient->getName(),patient->getDob(),patient->getDiagnosis());
    delete patient;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    QMessageBox box;
    box.setWindowTitle("Save before exit?");
    box.setText("Click Yes for Saving current data.");
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setDefaultButton(QMessageBox::Yes);
    int ret = box.exec();
    if (ret == QMessageBox::Yes)
        icfController->save();
    event->accept();
}

void MainWindow::on_saveButton_clicked()
{
    this->saveReport();
}

void MainWindow::fillTherComboBox()
{
    ui->therapeutcB->clear();
    for (int i=0; i<icfController->sizeOfTherapists(); i++) {
        ui->therapeutcB->addItem(QString::number(icfController->getTherapist(i)->getId()) + " " + icfController->getTherapist(i)->getSurname());
    }
}

void MainWindow::fillPatComboBox()
{
    ui->patientcB->clear();
    for (int i=0; i<icfController->sizeOfPatients(); i++) {
        ui->patientcB->addItem(QString::number(icfController->getPatient(i)->getId()) + " " + icfController->getPatient(i)->getSurname());
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

void MainWindow::fillReportForm(Report *rep)
{
    ui->dateEdit->setDate(rep->getDate());
    int index = ui->therapeutcB->findText(QString::number(rep->getTherapistId()), Qt::MatchContains);
    if (index >= 0)
        ui->therapeutcB->setCurrentIndex(index);
    ui->textEdit->setText(rep->getFreeText());
    ui->functionsWidget->hideAll();
    ui->structuresWidget->hideAll();
    ui->partizipationWidget->hideAll();
    ui->contextWidget->hideAll();
    for (int i=0; i<rep->sizeOfFunctions(); i++) {
        Function* actFunction = rep->getFunction(i);
        GUI_FunctionForm* actForm;
        switch (actFunction->getArt()) {
        case Function::function : actForm = ui->functionsWidget->setUnitVisible();
            break;
        case Function::structure : actForm = ui->structuresWidget->setUnitVisible();
            break;
        case Function::partizipation : actForm = ui->partizipationWidget->setUnitVisible();
            break;
        case Function::context : actForm = ui->contextWidget->setUnitVisible();
            break;
        default: std::cerr << "Kein GUI_FunctionForm* gefunden" << std::endl;
        }
        if (!actForm) continue;
        actForm->setId(actFunction->getId());
        actForm->setDescription(actFunction->getDescription());
        actForm->setValue(actFunction->getValue());
        actForm->setText(actFunction->getText());
    }
}

void MainWindow::on_printButton_clicked()
{
    icfController->printReport();
}

void MainWindow::on_actionManage_Therapists_triggered()
{
    GUI_ShowPerson* form = new GUI_ShowPerson(icfController,'t',this);
    form->setWindowTitle("Manage Therapists");
    form->exec();
    delete form;
    fillTherComboBox();
}

void MainWindow::on_actionManage_Patients_triggered()
{
    GUI_ShowPerson* form = new GUI_ShowPerson(icfController,'p',this);
    form->setWindowTitle("Manage Patients");
    form->exec();
    delete form;
    fillPatComboBox();
}

void MainWindow::saveFunctionAttributes(Report* rep, QList<GUI_FunctionForm*> list, Function::Art art) {
    foreach (GUI_FunctionForm* form, list) {
        Function* function = new Function();
        function->setArt(art);
        function->setId(form->getId());
        function->setDescription(form->getDescription());
        function->setValue(form->getValue());
        function->setText(form->getText());
        rep->addFunction(function);
    }
}

void MainWindow::saveReport() {
    Report* report = new Report(ui->dateEdit->date());
    QStringList pat = ui->patientcB->currentText().split(" ");
    report->setPatientId(pat[0].toInt());
    QStringList ther = ui->therapeutcB->currentText().split(" ");
    report->setTherapistId(ther[0].toInt());
    report->setFreeText(ui->textEdit->toPlainText());
    QList<GUI_FunctionForm*> functionsList = ui->functionsWidget->getActiveWidgets();
    saveFunctionAttributes(report, functionsList, Function::function);
    QList<GUI_FunctionForm*> structuresList = ui->structuresWidget->getActiveWidgets();
    saveFunctionAttributes(report,structuresList,Function::structure);
    QList<GUI_FunctionForm*> partizipationList = ui->partizipationWidget->getActiveWidgets();
    saveFunctionAttributes(report,partizipationList,Function::partizipation);
    QList<GUI_FunctionForm*> contextList = ui->contextWidget->getActiveWidgets();
    saveFunctionAttributes(report,contextList, Function::context);
    //First try to add as new Report
    if (icfController->addReport(report)) {
        QMessageBox* box = new QMessageBox(QMessageBox::Information, "Information", "Report added as new.");
        box->exec();
        delete box;
    }
    //Second try to override old Report
    else {
        QString msg;
        Report* oldRep;
        if ((oldRep = icfController->findReport(currentReportId))) {
            *oldRep = *report;
            oldRep->setId(currentReportId);
            msg = "Old Report overriden.";
        }
        //Third give Error Message
        else {
            msg = "Report with same Patient, Therapist AND Date already existing. Report not Saved!";
        }
        QMessageBox* box = new QMessageBox(QMessageBox::Information, "Information", msg);
        box->exec();
        delete box;
    }
    this->on_patientcB_currentIndexChanged(ui->patientcB->currentText());
}

void MainWindow::clearForm()
{
    currentReportId = 0;
    ui->functionsWidget->hideAll();
    ui->structuresWidget->hideAll();
    ui->partizipationWidget->hideAll();
    ui->contextWidget->hideAll();
    ui->textEdit->clear();
}

void MainWindow::on_reportcB_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "") return;
    if (arg1 == "New Report") {
        clearForm();
        return;
    }
    Report* actReport = icfController->findReport(arg1.toInt());
    if (actReport) {
        this->fillReportForm(actReport);
        currentReportId = actReport->getId();
    }
}

void MainWindow::on_patientcB_currentIndexChanged(const QString &arg1)
{
    ui->reportcB->clear();
    ui->reportcB->addItem("New Report");
    QStringList item = arg1.split(" ");
    QList<Report*> actReports = icfController->getReportsForId(item[0].toInt());
    if (!actReports.isEmpty()) {
        foreach (Report* rep, actReports) {
            ui->reportcB->addItem(QString::number(rep->getId()));
        }
    }
}

void MainWindow::on_deleteButton_clicked()
{
    if (icfController->removeReport(currentReportId)) {
        QMessageBox* box = new QMessageBox(QMessageBox::Information, "Information", "Report removed.");
        box->exec();
        delete box;
        this->on_patientcB_currentIndexChanged(ui->patientcB->currentText());
    }
}
