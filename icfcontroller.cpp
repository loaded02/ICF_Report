#include "icfcontroller.h"
#include <QDir>

int ICFController::patId = 2000;
int ICFController::therId = 1000;
int ICFController::repId = 5000;

ICFController::ICFController(QString baseDir)
    :m_baseDir(baseDir)
{
    QDir dir(baseDir + "/storage");
    if (!dir.exists())
        if (dir.mkdir(baseDir + "/storage"))
            qDebug() << "mkDir: " << baseDir << "/storage";

    DomParser patParser(&patients);
    patParser.readFile(m_baseDir + "/storage/patients.xml");
    foreach (Person* per, patients) {
        if (patId < per->getId())
            patId = per->getId();
    }
    patId++;
    DomParser therParser(&therapists);
    therParser.readFile(m_baseDir + "/storage/therapists.xml");
    foreach (Person* per, therapists) {
        if (therId < per->getId())
            therId = per->getId();
    }
    therId++;
    DomParser repParser(&reports);
    repParser.readFile(m_baseDir + "/storage/reports.xml");
    foreach (Report* rep, reports) {
        if (repId < rep->getId())
            repId = rep->getId();
    }
    repId++;
    DomParser codeParser(&icfCode);
    codeParser.readFile(m_baseDir + "/storage/icfcode.xml");
}

ICFController::~ICFController()
{
    foreach(Person* per, therapists) {
        delete per;
    }
    foreach (Person* per, patients) {
        delete per;
    }
    foreach (Report* rep, reports) {
        delete rep;
    }
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
                return 0;
            }
        }
    }
    return 1;
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
                return 0;
            }
        }
    }
    return 1;
}

int ICFController::addReport(Report *rep)
{
    //check if report allready exists
    for (int i=0; i<reports.size(); i++) {
        if (reports.at(i)->getDate() == rep->getDate() && reports.at(i)->getPatientId() == rep->getPatientId()
                && reports.at(i)->getTherapistId() == rep->getTherapistId()) {
            std::cerr << "Es existiert bereits ein Report mit diesen Daten" << std::endl;
            return 1;
        }
    }
    //setId
    if (rep->getId() == 0)
        rep->setId(repId++);
    reports.append(rep);
    return 0;
}

QList<Report *> ICFController::getReportsForId(int patId)
{
    QList<Report*> reportsForId;
    foreach(Report* rep, reports) {
        if (rep->getPatientId() == patId) {
            reportsForId.append(rep);
        }
    }
    return reportsForId;
}

Report *ICFController::findReport(int id)
{
    for (int i=0; i<reports.size(); i++){
        if (reports.at(i)->getId() == id) {
            return reports.at(i);
        }
    }
    return NULL;
}

int ICFController::removeReport(int id)
{
    if (Report* rep = this->findReport(id)) {
        for (auto it=reports.begin(); it!=reports.end(); it++) {
            if (*it == rep) {
                reports.erase(it);
                return 0;
            }
        }
    }
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
            therDOM.setAttribute("company", ther->getCompany());
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
            repDOM.setAttribute("type",actReport->getType());
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

void ICFController::createIcfCodeFile(QString filename)
{
    const int Indent = 4;

    QDomDocument doc;
    QDomElement root = doc.createElement("icfcodes");
    doc.appendChild(root);

    for (auto it=icfCode.begin(); it != icfCode.end(); it++) {
        QDomElement codeDOM = doc.createElement("icfcode");
        codeDOM.setAttribute("id",it->first);
        QDomElement textElement = doc.createElement("description");
        QDomText description = doc.createTextNode(it->second);
        textElement.appendChild(description);
        codeDOM.appendChild(textElement);
        root.appendChild(codeDOM);
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
        return;
    QTextStream out(&file);
    doc.save(out, Indent);
    file.close();
}

QString ICFController::getBaseDir() const
{
    return m_baseDir;
}

void ICFController::save()
{
    this->createFile(this->therapists, m_baseDir + "/storage/therapists.xml");
    this->createFile(this->patients, m_baseDir + "/storage/patients.xml");
    this->createFile(this->reports, m_baseDir + "/storage/reports.xml");
    this->createIcfCodeFile(m_baseDir + "/storage/icfcode.xml");
}

int ICFController::printReport(int repId)
{
    PrintWindow printWindow(this);
    return printWindow.printReport(repId);
}

QString ICFController::getIcfCodeDescription(QString code) {
    QString result;
    try {
        result = icfCode.at(code);
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
        result = "";
    }
    return result;
}

void ICFController::setIcfCodeDescription(QString code, QString description) {
    std::pair<std::map<QString,QString>::iterator,bool> ret;
    ret = icfCode.insert(std::pair<QString,QString>(code,description));
    //overrides existing key
    if (!ret.second) {
        icfCode[code] = description;
    }
}

QString ICFController::getIcfCode(int i) {
    if (i<0) return 0;
    int counter = 0;
    std::map<QString,QString>::iterator it = icfCode.begin();
    while (counter < i) {
        it++;
        counter++;
    }
    return it->first;
}
