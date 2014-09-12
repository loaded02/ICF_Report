#include "icfcontroller.h"

ICFController::ICFController()
{
    DomParser therParser(&therapists);
    therParser.readFile("therapists.xml");
    DomParser patParser(&patients);
    patParser.readFile("patients.xml");
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
            therDOM.setAttribute("surname",ther->getSurname());
            therDOM.setAttribute("name",ther->getName());
            root.appendChild(therDOM);
        }
        if (pat) {
            QDomElement patDOM = doc.createElement("patient");
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

void ICFController::save()
{
    this->createFile(this->therapists, "therapists.xml");
    this->createFile(this->patients, "patients.xml");
}
