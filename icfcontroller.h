#ifndef ICFCONTROLLER_H
#define ICFCONTROLLER_H

#include "report.h"
#include "patient.h"
#include "therapist.h"
#include "domparser.h"
#include "printwindow.h"
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class ICFController
{
public:
    ICFController();
    void addPatient(Patient* pat);
    Patient* getPatient(int i) {
        return static_cast<Patient*>(patients.at(i));
    }
    Patient* findPatient(int id);
    int sizeOfPatients() {
        return patients.size();
    }

    void addTherapist(Therapist* ther);
    Therapist* getTherapist(int i) {
        return static_cast<Therapist*>(therapists.at(i));
    }
    Therapist* findTherapist(int id);

    int sizeOfTherapists() {
        return therapists.size();
    }

    int addReport(Report* rep);
    Report* getReport(int pos);
    int sizeOfReports() {
        return reports.size();
    }

    void save();
    void printReport();
    QList<Person *>* getTherapists();

    QList<Person *>* getPatients();

private:
    void createFile(QList<Person*> persons, QString filename);
    void createFile(QList<Report*> reports, QString filename);
    static int therId;
    static int patId;
    static int repId;
    QList<Report*> reports;
    QList<Person*> patients;
    QList<Person*> therapists;
};

#endif // ICFCONTROLLER_H
