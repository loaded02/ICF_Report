#include "icfcontroller.h"

int ICFController::patId = 5000;
int ICFController::therId = 1000;
int ICFController::repId = 1000;

ICFController::ICFController()
{
    DomParser patParser(&patients);
    patParser.readFile("patients.xml");
    foreach (Person* per, patients) {
        if (patId < per->getId())
            patId = per->getId();
    }
    patId++;
    DomParser therParser(&therapists);
    therParser.readFile("therapists.xml");
    foreach (Person* per, therapists) {
        if (therId < per->getId())
            therId = per->getId();
    }
    therId++;
    DomParser repParser(&reports);
    repParser.readFile("reports.xml");
    foreach (Report* rep, reports) {
        if (repId < rep->getId())
            repId = rep->getId();
    }
    repId++;
}

void ICFController::addPatient(Patient* pat)
{
    if (pat->getId() == 0)
        pat->setId(patId++);
    patients.append(pat);
}

Patient *ICFController::findPatient(int id)
{
    for (int i=0; i<patients.size(); i++){
        if (patients.at(i)->getId() == id) {
            return static_cast<Patient*>(patients.at(i));
        }
    }
    return NULL;
}

int ICFController::removePatient(int id)
{
    if (Patient* pat = this->findPatient(id)) {
        for (auto it=patients.begin(); it!=patients.end(); it++) {
            if (*it == pat) {
                patients.erase(it);
                return 1;
            }
        }
    }
    return 0;
}


void ICFController::addTherapist(Therapist* ther)
{
    if (ther->getId() == 0)
        ther->setId(therId++);
    therapists.append(ther);
}

Therapist *ICFController::findTherapist(int id)
{
    for (int i=0; i<therapists.size(); i++){
        if (therapists.at(i)->getId() == id) {
            return static_cast<Therapist*>(therapists.at(i));
        }
    }
    return NULL;
}

int ICFController::removeTherapist(int id)
{
    if (Therapist* ther = this->findTherapist(id)) {
        for (auto it=therapists.begin(); it!=therapists.end(); it++) {
            if (*it == ther) {
                therapists.erase(it);
                return 1;
            }
        }
    }
    return 0;
}

int ICFController::addReport(Report *rep)
{
    //check if report allready exists
    for (int i=0; i<reports.size(); i++) {
        if (reports.at(i)->getDate() == rep->getDate() && reports.at(i)->getPatientId() == rep->getPatientId()
                && reports.at(i)->getTherapistId() == rep->getTherapistId()) {
            std::cerr << "Es existiert bereits ein Report mit diesen Daten" << std::endl;
            return 0;
        }
    }
    //setId
    if (rep->getId() == 0)
        rep->setId(repId++);
    reports.append(rep);
    return 1;
}

void ICFController::createFile(QList<Person*> persons, QString filename)
{
    const int Indent = 4;

    QDomDocument doc;
    QDomElement root = doc.createElement("person");
    doc.appendChild(root);

    foreach (Person* actPerson, persons) {
        Therapist* ther = dynamic_cast<Therapist*>(actPerson);
        Patient* pat = dynamic_cast<Patient*>(actPerson);
        if (ther) {
            QDomElement therDOM = doc.createElement("therapist");
            therDOM.setAttribute("id",ther->getId());
            therDOM.setAttribute("surname",ther->getSurname());
            therDOM.setAttribute("name",ther->getName());
            root.appendChild(therDOM);
        }
        if (pat) {
            QDomElement patDOM = doc.createElement("patient");
            patDOM.setAttribute("id",pat->getId());
            patDOM.setAttribute("surname",pat->getSurname());
            patDOM.setAttribute("name",pat->getName());
            patDOM.setAttribute("diagnosis",pat->getDiagnosis());
            patDOM.setAttribute("dob",pat->getDob().toString());
            root.appendChild(patDOM);
        }
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
        return;
    QTextStream out(&file);
    doc.save(out, Indent);
    file.close();
}

void ICFController::createFile(QList<Report *> reports, QString filename)
{
    const int Indent = 4;

    QDomDocument doc;
    QDomElement root = doc.createElement("reports");
    doc.appendChild(root);

    foreach (Report* actReport, reports) {
            QDomElement repDOM = doc.createElement("report");
            repDOM.setAttribute("id",QString::number(actReport->getId()));
            repDOM.setAttribute("date", actReport->getDate().toString());
            repDOM.setAttribute("patient",actReport->getPatientId());
            repDOM.setAttribute("therapist",actReport->getTherapistId());
            QDomElement textElement = doc.createElement("freetext");
            QDomText freeText = doc.createTextNode(actReport->getFreeText());
            textElement.appendChild(freeText);
            repDOM.appendChild(textElement);
            root.appendChild(repDOM);
            for (int i=0; i<actReport->sizeOfFunctions(); i++) {
                Function* actFunction = actReport->getFunction(i);
                QString label;
                switch (actFunction->getArt()) {
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

                QDomElement funcDOM = doc.createElement(label);
                funcDOM.setAttribute("art",actFunction->getArt());
                funcDOM.setAttribute("id",actFunction->getId());
                funcDOM.setAttribute("description",actFunction->getDescription());
                funcDOM.setAttribute("value",actFunction->getValue());
                QDomText text = doc.createTextNode(actFunction->getText());
                funcDOM.appendChild(text);
                repDOM.appendChild(funcDOM);
            }
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
        return;
    QTextStream out(&file);
    doc.save(out, Indent);
    file.close();
}

void ICFController::save()
{
    this->createFile(this->therapists, "therapists.xml");
    this->createFile(this->patients, "patients.xml");
    this->createFile(this->reports, "reports.xml");
}

void ICFController::printReport()
{
    QStringList headerList;
    headerList.append("1.1.2014");
    Patient* pat = static_cast<Patient*>(patients.at(0));
    headerList.append(pat->getName() + " " + pat->getSurname());
    headerList.append(pat->getDob().toString());
    headerList.append(pat->getDiagnosis());
    headerList.append("ICF Core Set - Apoplex");
    headerList.append(therapists.at(0)->getName() + " " + therapists.at(0)->getSurname());
    PrintWindow printWindow;
    printWindow.printHeader(headerList);
}
