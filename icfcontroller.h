#ifndef ICFCONTROLLER_H
#define ICFCONTROLLER_H

#include "report.h"
#include "patient.h"
#include "therapist.h"
#include "domparser.h"
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class ICFController
{
public:
    ICFController();
    void addPatient(Patient pat);
    void addTherapist(Therapist ther);
    void addReport(Report rep);
    Report getReport(int pos);
    int sizeReports();
    void createXMLFile(QList<Person*> persons, QString filename);
    void save();
private:
    QList<Report> reports;
    QList<Person> patients;
    QList<Person*> therapists;
};

#endif // ICFCONTROLLER_H
