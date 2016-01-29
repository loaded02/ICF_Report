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
#include <map>

/*
 * Controls Businesslogic entities.
 * Also has at Runtime the lists of patients, therapists, reports and icfCodes
*/

class ICFController
{
public:
    /*Default constructor*/
    ICFController(QString baseDir);
    /*Destructor*/
    ~ICFController();
    /*Appends Patient to Patient List*/
    void addPatient(Patient* pat);
    /*Returns pointer to Patient at index i*/
    Patient* getPatient(int i) {
        return static_cast<Patient*>(patients.at(i));
    }
    /*Returns pointer to Patient with given id
    * or NULL if Patient doesn't exist.*/
    Patient* findPatient(int id);
    /*Number of Patients in Patient List*/
    int sizeOfPatients() {
        return patients.size();
    }
    /*Removes Patient from List if he exists. Return 1 in case of sucess. Else 0.*/
    int removePatient(int id);
    /*Appends Therapist to Therapist List*/
    void addTherapist(Therapist* ther);
    /*Returns pointer to Therapist at index i*/
    Therapist* getTherapist(int i) {
        return static_cast<Therapist*>(therapists.at(i));
    }
    /*Returns pointer to Therapist with given id
    * or NULL if Therapist doesn't exist.*/
    Therapist* findTherapist(int id);
    /*Number of Therapists in Therapist List*/
    int sizeOfTherapists() {
        return therapists.size();
    }
    /*Removes Therapist from List if he exists. Return 1 in case of sucess. Else 0.*/
    int removeTherapist(int id);
    /*Appends Report to Report List*/
    int addReport(Report* rep);
    /*Returns pointer to Report at index i*/
    Report* getReport(int pos);
    /*Number of Report in Report List*/
    int sizeOfReports() {
        return reports.size();
    }
    /*Returns all Reports corresponding for certain Patient id*/
    QList<Report*> getReportsForId(int patId);
    /*Returns pointer to Report with given id
    * or NULL if Report doesn't exist.*/
    Report* findReport(int id);
    /*Removes Report from List if he exists. Return 1 in case of sucess. Else 0.*/
    int removeReport(int id);
    /*Saves Reports, Therapists, Patients and ICF Codes in XML Files*/
    void save();
    /*prints current report*/
    void printReport(int repId);
    /*returns Description corresponding to code String*/
    QString getIcfCodeDescription(QString code);
    /*Inserts the key (code), value (description) pair into Code list.
    *Overrides pair if key already exists.*/
    void setIcfCodeDescription(QString code, QString description);
    /*Number of ICF Codes in Code List*/
    int sizeOfIcfCodes() {
        return icfCode.size();
    }
    /*Return ICF Code at position i in Code list*/
    QString getIcfCode(int i);

    QString getBaseDir() const;

private:
    void createFile(QList<Person*> persons, QString filename);
    void createFile(QList<Report*> reports, QString filename);
    void createIcfCodeFile(QString filename);
    static int therId;
    static int patId;
    static int repId;
    QList<Report*> reports;
    QList<Person*> patients;
    QList<Person*> therapists;
    std::map<QString,QString> icfCode;
    QString m_baseDir;
};

#endif // ICFCONTROLLER_H
