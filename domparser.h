#ifndef DOMPARSER_H
#define DOMPARSER_H

/*
* Parses XML Document with 2 hierarchy steps
* and puts them into an QVector. Used for Person class.
*/

#include <QList>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <iostream>
#include "person.h"
#include "therapist.h"
#include "patient.h"
#include "report.h"

class DomParser
{
public:
    DomParser(QList<Person*>* daten);
    DomParser(QList<Report*>* daten);

    bool readFile(const QString &fileName);

private:
    void parseRootElement(const QDomElement &element);
    void parseTherapist(const QDomElement &element);
    void parsePatient(const QDomElement &element);
    void parseReport(const QDomElement element);
    void parseFunction(const QDomElement &element,
                          Function *parent);
    QList<Person*>* daten;
    QList<Report*>* reports;
};

#endif // DOMPARSER_H
