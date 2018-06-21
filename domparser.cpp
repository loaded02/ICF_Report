#include "domparser.h"


DomParser::DomParser(QList<Person*>* daten)
    :daten(daten){

}

DomParser::DomParser(QList<Report *> *daten)
    :reports(daten){

}

DomParser::DomParser(std::map<QString, QString> *daten)
    :icfCodes(daten){

}

bool DomParser::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        std::cerr << "Error: Cannot read file " << qPrintable(fileName)
                  << ": " << qPrintable(file.errorString())
                  << std::endl;
        return false;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument doc;
    if (!doc.setContent(&file, false, &errorStr, &errorLine,
                        &errorColumn)) {
        std::cerr << "Error: Parse error at line " << errorLine << ", "
                  << "column " << errorColumn << ": "
                  << qPrintable(errorStr) << std::endl;
        return false;
    }

    QDomElement root = doc.documentElement();

    if (root.tagName() == "person" || root.tagName() == "reports" || root.tagName() == "icfcodes") {
        parseRootElement(root);
    }
    else {
        std::cerr << "Error: Not a known file" << std::endl;
        return false;
    }
    return true;
}

void DomParser::parseRootElement(const QDomElement &element)
{
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "therapist") {
            parseTherapist(child.toElement());
        }
        else if (child.toElement().tagName() == "patient") {
            parsePatient(child.toElement());
        }
        else if (child.toElement().tagName() == "report") {
            parseReport(child.toElement());
        }
        else if (child.toElement().tagName() == "icfcode") {
            parseIcfCode(child.toElement());
        }
        child = child.nextSibling();
    }
}

void DomParser::parseIcfCode(const QDomElement &element)
{
    QString id = element.attribute("id");
    QString description;
    QDomNode child = element.firstChild();
    if (child.toElement().tagName() == "description") {
        description = child.toElement().text();
    }
    icfCodes->insert(std::pair<QString,QString>(id,description));
}

void DomParser::parseTherapist(const QDomElement &element)
{
    Therapist* item = new Therapist(element.attribute("surname"));
    item->setId(element.attribute("id").toInt());
    item->setName(element.attribute("name"));
    item->setCompany(element.attribute("company"));
    daten->append(item);
}

void DomParser::parsePatient(const QDomElement &element)
{
    Patient* item = new Patient(element.attribute("surname"));
    item->setId(element.attribute("id").toInt());
    item->setName(element.attribute("name"));
    item->setDiagnosis(element.attribute("diagnosis"));
    item->setDob(QDate::fromString(element.attribute("dob")));
    daten->append(item);
}

void DomParser::parseReport(const QDomElement element)
{
    Report* item = new Report(QDate::fromString(element.attribute("date")));
    item->setId(element.attribute("id").toInt());
    item->setPatientId(element.attribute("patient").toInt());
    item->setTherapistId(element.attribute("therapist").toInt());
    item->setType(element.attribute("type"));

    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        Function* func = new Function();
        if (child.toElement().tagName() == "function") {
            func->setArt(Function::function);
        } else if (child.toElement().tagName() == "structure") {
            func->setArt(Function::structure);
        } else if (child.toElement().tagName() == "partizipation") {
            func->setArt(Function::partizipation);
        } else if (child.toElement().tagName() == "context") {
            func->setArt(Function::context);
        } else if (child.toElement().tagName() == "freetext") {
            item->setFreeText(child.toElement().text());
            child = child.nextSibling();
            continue;
        }
        parseFunction(child.toElement(),func);
        item->addFunction(func);
        child = child.nextSibling();
    }
    reports->append(item);
}

void DomParser::parseFunction(const QDomElement &element, Function *parent)
{
    parent->setId(element.attribute("id"));
    parent->setDescription(element.attribute("description"));
    parent->setValue(element.attribute("value").toInt());
    parent->setText(element.text());
}
