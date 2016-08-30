#include "gui_report.h"
#include "ui_gui_report.h"
#include <QMessageBox>
#include <QInputDialog>

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
    ui->dateEdit->setDate(QDate::currentDate());
    QList<GUI_FunctionForm*> list = ui->contextWidget->getAllWidgets();
    foreach (GUI_FunctionForm* form, list) {
        form->showContextRadio();
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
    QMessageBox msgBox;
    msgBox.setText("Delete report.");
    msgBox.setInformativeText("Do you really want to delete the report?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Cancel) return;
    if (!m_icfController->removeReport(currentReportId)) {
        QMessageBox box;
        box.setText("Report deleted.");
        box.exec();
        this->on_patientcB_currentIndexChanged(ui->patientcB->currentText());
    }
}

void GUI_Report::on_printButton_clicked()
{
    if (ui->reportcB->currentText() == "New Report") return;
    if (!m_icfController->printReport(ui->reportcB->currentText().toInt())) {
        QMessageBox box;
        box.setText("Report printed.");
        box.exec();
    }
}

void GUI_Report::on_saveButton_clicked()
{
    if (!saveReport()) {
        QMessageBox box;
        box.setText("Report saved.");
        box.exec();
    } else {
        QMessageBox box;
        box.setText("Change date, patient or therapist to save report.");
        box.exec();
    }
}

void GUI_Report::clearForm()
{
    currentReportId = 0;
    ui->functionsWidget->hideAll();
    ui->structuresWidget->hideAll();
    ui->partizipationWidget->hideAll();
    ui->contextWidget->hideAll();
    ui->textEdit->clear();
    ui->dateEdit->setDate(QDate::currentDate());
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

int GUI_Report::saveReport()
{
    Report* report = new Report(ui->dateEdit->date());
    QStringList pat = ui->patientcB->currentText().split(" ");
    report->setPatientId(pat[0].toInt());
    QStringList ther = ui->therapeutcB->currentText().split(" ");
    report->setTherapistId(ther[0].toInt());
    report->setFreeText(ui->textEdit->toPlainText());
    report->setType(ui->lineEditRepType->text());
    QList<GUI_FunctionForm*> functionsList = ui->functionsWidget->getActiveWidgets();
    saveFunctionAttributes(report, functionsList, Function::function);
    QList<GUI_FunctionForm*> structuresList = ui->structuresWidget->getActiveWidgets();
    saveFunctionAttributes(report,structuresList,Function::structure);
    QList<GUI_FunctionForm*> partizipationList = ui->partizipationWidget->getActiveWidgets();
    saveFunctionAttributes(report,partizipationList,Function::partizipation);
    QList<GUI_FunctionForm*> contextList = ui->contextWidget->getActiveWidgets();
    saveFunctionAttributes(report,contextList, Function::context);
    //First try to add as new Report
    if (!m_icfController->addReport(report)) {
        QMessageBox box;
        box.setText("Report added as new.");
        box.exec();
        //update Report Combobox
        this->on_patientcB_currentIndexChanged(ui->patientcB->currentText());
        int index;
        if ((index = ui->reportcB->findText(QString::number(report->getId()))) != -1)
            ui->reportcB->setCurrentIndex(index);
        return 0;
    }
    //Second try to override old Report
    else {
        Report* oldRep;
        if ((oldRep = m_icfController->findReport(currentReportId))) {
            QMessageBox msgBox;
            msgBox.setText("There is already a report for this patient and this date.");
            msgBox.setInformativeText("Do you want to override the old report?");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int ret = msgBox.exec();
            if (ret == QMessageBox::Ok) {
                *oldRep = *report; //old becomes new Report
                oldRep->setId(currentReportId);
                return 0;
            }
            return 1;
        }
    }
    return 1;
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
    ui->lineEditRepType->setText(rep->getType());
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
        GUI_FunctionForm* actForm = 0;
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

void GUI_Report::on_lineEditRepType_returnPressed()
{
    Report* rep = m_icfController->findReport(currentReportId);
    if (rep) {
        rep->setType(ui->lineEditRepType->text());
        QMessageBox box;
        box.setText("Report Type changed.");
        box.exec();
    }
}

void GUI_Report::on_closeButton_clicked()
{
    close();
}
