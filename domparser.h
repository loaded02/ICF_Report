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

class DomParser
{
public:
    DomParser(QList<Person*>* daten);

    bool readFile(const QString &fileName);

private:
    void parseRootElement(const QDomElement &element);
    void parseTherapist(const QDomElement &element);
    void parsePatient(const QDomElement &element);
    void parseSecondChild(const QDomElement &element,
                          Person* parent);
    QList<Person*>* daten;
};

#endif // DOMPARSER_H
