#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <QList>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <iostream>
#include <QStringList>
#include <QDebug>
#include "person.h"
#include "therapist.h"
#include "patient.h"
#include "report.h"

/*
* Parses XML Document with 2 hierarchy steps
* and puts them into an QVector. Used for all saved Datatypes (Person, Report, ICFCodes)
*/

class DomParser
{
public:
    DomParser(QList<Person*>* daten);
    DomParser(QList<Report*>* daten);
    DomParser(std::map<QString,QString>* daten);

    bool readFile(const QString &fileName);

private:
    void parseRootElement(const QDomElement &element);
    void parseIcfCode(const QDomElement &element);
    void parseTherapist(const QDomElement &element);
    void parsePatient(const QDomElement &element);
    void parseReport(const QDomElement element);
    void parseFunction(const QDomElement &element,
                          Function *parent);
    QList<Person*>* daten;
    QList<Report*>* reports;
    std::map<QString,QString>* icfCodes;
};

#endif // DOMPARSER_H
