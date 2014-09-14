#ifndef REPORT_H
#define REPORT_H

#include "patient.h"
#include "therapist.h"
#include "function.h"

class Report
{
public:
    Report(QDate date);
    ~Report();
    Patient getPatient() const;
    void setPatient(const Patient &value);

    Therapist getTherapist() const;
    void setTherapist(const Therapist &value);

    QDate getDate() const;
    void setDate(const QDate &value);

    QString getFreeText() const;
    void setFreeText(const QString &value);

    int sizeOfFunctions() {
        return functions.size();
    }
    Function* getFunction(int i) {
        return functions.at(i);
    }
    void addFunction(Function* funct) {
        functions.append(funct);
    }

private:
    Patient patient;
    Therapist therapist;
    QDate date;
    QList<Function*> functions;
    QString freeText;
};

#endif // REPORT_H
