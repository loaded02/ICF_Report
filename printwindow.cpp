#include "printwindow.h"
#include <QDomDocument>
#include <QDomElement>
#include <QString>
#include <QDebug>
#include "patient.h"
#include "therapist.h"

PrintWindow::PrintWindow(ICFController* icfController, QDialog *parent)
    :QDialog(parent), icfController(icfController)
{
}

PrintWindow::~PrintWindow()
{

}

int PrintWindow::printReport(int repId)
{
    Report* report;
    if ((report = icfController->findReport(repId))) {
        createXmlReport(*report);
        return 0;
    }
    return 1;
}

void PrintWindow::createXmlReport(Report& rep) {
    QDomDocument doc;
    doc.insertBefore(doc.createProcessingInstruction("xml-stylesheet", "type=\"text/xsl\" href=\"layout/report.xsl\""),doc.documentElement());
    doc.insertBefore(doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\""),doc.documentElement());
    QDomElement root = doc.createElement("report");
    doc.appendChild(root);

    QDomElement repId = doc.createElement("id");
    root.appendChild(repId);
    QDomText repIdTxt = doc.createTextNode(QString::number(rep.getId()));
    repId.appendChild(repIdTxt);

    QDomElement repDate = doc.createElement("date");
    root.appendChild(repDate);
    QDomText repDateTxt = doc.createTextNode(rep.getDate().toString("dd.MM.yyyy"));
    repDate.appendChild(repDateTxt);

    QDomElement repType = doc.createElement("type");
    root.appendChild(repType);
    QDomText repTypeTxt = doc.createTextNode(rep.getType());
    repType.appendChild(repTypeTxt);

    createXmlPatient(rep,doc,root);
    createXmlTherapist(rep,doc, root);
    createXmlFunction(rep,doc, root);

    QDomElement free = doc.createElement("freetext");
    root.appendChild(free);
    QDomText freeTxt = doc.createTextNode(rep.getFreeText());
    free.appendChild(freeTxt);

    QFile file(icfController->getBaseDir() + "report.xml");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
        return;
    QTextStream out(&file);
    const int Indent = 4;
    doc.save(out,Indent);
    file.close();
}

void PrintWindow::createXmlTherapist(Report& rep, QDomDocument& doc, QDomElement& root) {
    Therapist* ther = icfController->findTherapist(rep.getTherapistId());
    if (ther) {
        QDomElement therapist = doc.createElement("therapist");
        root.appendChild(therapist);
        QDomElement therId = doc.createElement("id");
        therapist.appendChild(therId);
        QDomText therIdTxt = doc.createTextNode(QString::number(ther->getId()));
        therId.appendChild(therIdTxt);

        QDomElement therName = doc.createElement("name");
        therapist.appendChild(therName);
        QDomText therNameTxt = doc.createTextNode(ther->getName());
        therName.appendChild(therNameTxt);

        QDomElement therSurname = doc.createElement("surname");
        therapist.appendChild(therSurname);
        QDomText therSurnameTxt = doc.createTextNode(ther->getSurname());
        therSurname.appendChild(therSurnameTxt);

        QDomElement therOffice = doc.createElement("office");
        therapist.appendChild(therOffice);
        QDomText therOfficeTxt = doc.createTextNode(ther->getCompany());
        therOffice.appendChild(therOfficeTxt);
    }
}

void PrintWindow::createXmlPatient(Report& rep, QDomDocument& doc, QDomElement& root) {
    Patient* patient = icfController->findPatient(rep.getPatientId());
    if (patient) {
    QDomElement pat = doc.createElement("patient");
    root.appendChild(pat);
    QDomElement patId = doc.createElement("id");
    pat.appendChild(patId);
    QDomText patIdTxt = doc.createTextNode(QString::number(patient->getId()));
    patId.appendChild(patIdTxt);

    QDomElement patName = doc.createElement("name");
    pat.appendChild(patName);
    QDomText patNameTxt = doc.createTextNode(patient->getName());
    patName.appendChild(patNameTxt);

    QDomElement patSurname = doc.createElement("surname");
    pat.appendChild(patSurname);
    QDomText patSurnameTxt = doc.createTextNode(patient->getSurname());
    patSurname.appendChild(patSurnameTxt);

    QDomElement patDob = doc.createElement("dob");
    pat.appendChild(patDob);
    QDomText patDobTxt = doc.createTextNode(patient->getDob().toString("dd.MM.yyyy"));
    patDob.appendChild(patDobTxt);

    QDomElement patDiag = doc.createElement("diagnosis");
    pat.appendChild(patDiag);
    QDomText patDiagTxt = doc.createTextNode(patient->getDiagnosis());
    patDiag.appendChild(patDiagTxt);
    }
}

void PrintWindow::createXmlFunction(Report& rep, QDomDocument& doc, QDomElement& root) {
    for (int i=0; i<rep.sizeOfFunctions(); i++) {
        Function* actFunc = rep.getFunction(i);
        QString label;
        switch (actFunc->getArt()) {
        case Function::function : label = "function";
            break;
        case Function::structure : label = "structure";
            break;
        case Function::partizipation : label = "partizipation";
            break;
        case Function::context : label = "context";
            break;
        default: ;
        }

        QDomElement func = doc.createElement(label);
        root.appendChild(func);
        QDomElement id = doc.createElement("id");
        func.appendChild(id);
        QDomText idTxt = doc.createTextNode(actFunc->getId());
        id.appendChild(idTxt);

        QDomElement desc = doc.createElement("description");
        func.appendChild(desc);
        QDomText descTxt = doc.createTextNode(actFunc->getDescription());
        desc.appendChild(descTxt);

        QDomElement val = doc.createElement("value");
        func.appendChild(val);
        QDomText valTxt = doc.createTextNode(QString::number(actFunc->getValue()));
        val.appendChild(valTxt);

        QDomElement txt = doc.createElement("freetext");
        func.appendChild(txt);
        QDomText txtTxt = doc.createTextNode(actFunc->getText());
        txt.appendChild(txtTxt);
    }
}
