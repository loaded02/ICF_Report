#include "domparser.h"


DomParser::DomParser(QList<Person*>* daten)
    :daten(daten){

}

DomParser::DomParser(QList<Report *> *daten)
    :reports(daten){

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

    if (root.tagName() == "person" || root.tagName() == "reports") {
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

        }
        child = child.nextSibling();
    }
}

void DomParser::parseTherapist(const QDomElement &element)
{
    Therapist* item = new Therapist(element.attribute("surname"));
    item->setId(element.attribute("id").toInt());
    item->setName(element.attribute("name"));
    daten->append(item);

//    QDomNode child = element.firstChild();
//    while (!child.isNull()) {
//        if (child.toElement().tagName() == "entry") {
//            parseEntryElement(child.toElement(), item);
//        } else if (child.toElement().tagName() == "page") {
//            parsePageElement(child.toElement(), item);
//        }
//        child = child.nextSibling();
    //    }
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
    //attr
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
        }
        parseSecondChild(child.toElement(),func);
        child = child.nextSibling();
    }
}

void DomParser::parseSecondChild(const QDomElement &element, Function *parent)
{
//    QString page = element.text();
//    QString allPages = parent->text(1);
//    if (!allPages.isEmpty())
//        allPages += ", ";
//    allPages += page;
//    parent->setText(1, allPages);
}
