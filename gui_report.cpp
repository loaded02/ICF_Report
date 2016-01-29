#include "gui_report.h"
#include "ui_gui_report.h"
#include <QMessageBox>

GUI_Report::GUI_Report(ICFController *icfController, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUI_Report), m_icfController(icfController),currentReportId(0)
{
    ui->setupUi(this);
    this->setWindowTitle("ICF Report");
    ui->structuresWidget->setLabel("Bodystructures");
    ui->partizipationWidget->setLabel("Participation");
    ui->contextWidget->setLabel("Context Factors");
    this->fillTherComboBox();
    this->fillPatComboBox();
    connectSignals();
    for (int i=0; i<m_icfController->sizeOfIcfCodes(); i++) {
        emit addIcfCodeToForm(m_icfController->getIcfCode(i));
    }
}

GUI_Report::~GUI_Report()
{
    delete ui;
}

void GUI_Report::icfIdChanged(QString icfId, int rnd)
{
    QString value;
    if ((value = m_icfController->getIcfCodeDescription(icfId)) == "") {
        value = QInputDialog::getText(this, "Enter Description", QString::null,QLineEdit::Normal,"Description");
        m_icfController->setIcfCodeDescription(icfId,value);
    }
    emit changeDescription(value,rnd);
}

void GUI_Report::on_patientcB_currentIndexChanged(const QString &arg1)
{
    ui->reportcB->clear();
    ui->reportcB->addItem("New Report");
    QStringList item = arg1.split(" ");
    QList<Report*> actReports = m_icfController->getReportsForId(item[0].toInt());
    if (!actReports.isEmpty()) {
        foreach (Report* rep, actReports) {
            ui->reportcB->addItem(QString::number(rep->getId()));
        }
    }
}

void GUI_Report::on_therapeutcB_currentIndexChanged(const QString &arg1)
{

}

void GUI_Report::on_reportcB_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "") return;
    if (arg1 == "New Report") {
        clearForm();
        return;
    }
    Report* actReport = m_icfController->findReport(arg1.toInt());
    if (actReport) {
        this->fillReportForm(actReport);
        currentReportId = actReport->getId();
    }
}

void GUI_Report::on_cancelButton_clicked()
{
    ui->reportcB->setCurrentIndex(0);
}

void GUI_Report::on_deleteButton_clicked()
{
    if (m_icfController->removeReport(currentReportId)) {
        QMessageBox* box = new QMessageBox(QMessageBox::Information, "Information", "Report removed.");
        box->exec();
        delete box;
        this->on_patientcB_currentIndexChanged(ui->patientcB->currentText());
    }
}

void GUI_Report::on_printButton_clicked()
{
    if (ui->reportcB->currentText() == "New Report") return;
    m_icfController->printReport(ui->reportcB->currentText().toInt());
}

void GUI_Report::on_saveButton_clicked()
{
    this->saveReport();
}

void GUI_Report::clearForm()
{
    currentReportId = 0;
    ui->functionsWidget->hideAll();
    ui->structuresWidget->hideAll();
    ui->partizipationWidget->hideAll();
    ui->contextWidget->hideAll();
    ui->textEdit->clear();
}

void GUI_Report::connectSignals()
{
    QList<GUI_FunctionForm*> list = ui->functionsWidget->getAllWidgets();
    connectLoop(list);
    list.clear();
    list = ui->structuresWidget->getAllWidgets();
    connectLoop(list);
    list.clear();
    list = ui->partizipationWidget->getAllWidgets();
    connectLoop(list);
    list.clear();
    list = ui->contextWidget->getAllWidgets();
    connectLoop(list);
}

void GUI_Report::connectLoop(QList<GUI_FunctionForm *> list)
{
    foreach (GUI_FunctionForm* form, list) {
        connect(form,SIGNAL(idChanged(QString,int)),this,SLOT(icfIdChanged(QString,int)));
        connect(this,SIGNAL(changeDescription(QString,int)),form,SLOT(changeDescription(QString,int)));
        connect(this,SIGNAL(addIcfCodeToForm(QString)),form,SLOT(addIcfCodeToCb(QString)));
    }
}

void GUI_Report::saveFunctionAttributes(Report *rep, QList<GUI_FunctionForm *> list, Function::Art art)
{
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

void GUI_Report::saveReport()
{
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
    if (m_icfController->addReport(report)) {
        QMessageBox* box = new QMessageBox(QMessageBox::Information, "Information", "Report added as new.");
        box->exec();
        delete box;
        //update Report Combobox
        this->on_patientcB_currentIndexChanged(ui->patientcB->currentText());
        int index;
        if ((index = ui->reportcB->findText(QString::number(report->getId()))) != -1)
            ui->reportcB->setCurrentIndex(index);
    }
    //Second try to override old Report
    else {
        QString msg;
        Report* oldRep;
        if ((oldRep = m_icfController->findReport(currentReportId))) {
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
}

void GUI_Report::fillTherComboBox()
{
    ui->therapeutcB->clear();
    for (int i=0; i<m_icfController->sizeOfTherapists(); i++) {
        ui->therapeutcB->addItem(QString::number(m_icfController->getTherapist(i)->getId()) + " " + m_icfController->getTherapist(i)->getSurname());
    }
}

void GUI_Report::fillPatComboBox()
{
    ui->patientcB->clear();
    for (int i=0; i<m_icfController->sizeOfPatients(); i++) {
        ui->patientcB->addItem(QString::number(m_icfController->getPatient(i)->getId()) + " " + m_icfController->getPatient(i)->getSurname());
    }
}

void GUI_Report::fillReportForm(Report *rep)
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
//        actForm->setDescription(actFunction->getDescription());
        actForm->setValue(actFunction->getValue());
        actForm->setText(actFunction->getText());
    }
}
