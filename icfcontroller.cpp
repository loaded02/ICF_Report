#include "icfcontroller.h"

ICFController::ICFController()
{
    //Test
//    Therapist* ther1 = new Therapist("Meier");
//    ther1->setName("Max");
//    therapists.append(ther1);
//    Therapist* ther2 = new Therapist("Mueller");
//    ther2->setName("Moritz");
//    therapists.append(ther2);
    DomParser parser(&therapists);
    parser.readFile("therapists.xml");
}

void ICFController::createXMLFile(QList<Person*> persons, QString filename)
{
    const int Indent = 4;

    QDomDocument doc;
    QDomElement root = doc.createElement("person");
    doc.appendChild(root);

    foreach (Person* actPerson, persons) {
        QDomElement person = doc.createElement("therapist");
        person.setAttribute("surname",actPerson->getSurname());
        person.setAttribute("name",actPerson->getName());
//        QDomElement surname = doc.createElement("surname");
//        QDomElement name = doc.createElement("name");
//        QDomText actName = doc.createTextNode(actPerson.getName());
//        QDomText actSurname = doc.createTextNode(actPerson.getSurname());
        root.appendChild(person);
//        person.appendChild(surname);
//        person.appendChild(name);
//        surname.appendChild(actSurname);
//        name.appendChild(actName);
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
//    this->createXMLFile(this->patients, "patients.xml");
}
