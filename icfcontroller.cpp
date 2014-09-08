#include "icfcontroller.h"

ICFController::ICFController()
{
    //Test
    Therapist ther1 = Therapist("Meier");
    ther1.setName("Max");
    therapists.append(ther1);
    Therapist ther2 = Therapist("Mueller");
    ther2.setName("Moritz");
    therapists.append(ther2);
}

void ICFController::createXMLFile(QList<Person> persons, QString filename)
{
    const int Indent = 4;

    QDomDocument doc;
    QDomElement root = doc.createElement("doc");
    doc.appendChild(root);

    foreach (Person actPerson, persons) {
        QDomElement person = doc.createElement("person");
        QDomElement surname = doc.createElement("surname");
        QDomElement name = doc.createElement("name");
        QDomText actName = doc.createTextNode(actPerson.getName());
        QDomText actSurname = doc.createTextNode(actPerson.getSurname());
        root.appendChild(person);
        person.appendChild(surname);
        person.appendChild(name);
        surname.appendChild(actSurname);
        name.appendChild(actName);
        //dynamic_cast Patient
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QTextStream out(&file);
    doc.save(out, Indent);
}

void ICFController::save()
{
    this->createXMLFile(this->therapists, "therapists.xml");
    this->createXMLFile(this->patients, "patients.xml");
}
