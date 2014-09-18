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
    ~ICFController();
    void addPatient(Patient* pat);
    Patient* getPatient(int i) {
        return static_cast<Patient*>(patients.at(i));
    }
    Patient* findPatient(int id);
    int sizeOfPatients() {
        return patients.size();
    }
    int removePatient(int id);

    void addTherapist(Therapist* ther);
    Therapist* getTherapist(int i) {
        return static_cast<Therapist*>(therapists.at(i));
    }
    Therapist* findTherapist(int id);

    int sizeOfTherapists() {
        return therapists.size();
    }
    int removeTherapist(int id);

    int addReport(Report* rep);
    Report* getReport(int pos);
    int sizeOfReports() {
        return reports.size();
    }
    QList<Report*> getReportsForId(int patId);
    Report* findReport(int id);
    int removeReport(int id);

    void save();
    void printReport(int repId);

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
