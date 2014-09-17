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

    int getPatientId() const;
    void setPatientId(int value);

    int getTherapistId() const;
    void setTherapistId(int value);

    int getId() const;
    void setId(int value);

private:
    int id;
    int patientId;
    int therapistId;
    QDate date;
    QList<Function*> functions;
    QString freeText;
};

#endif // REPORT_H
