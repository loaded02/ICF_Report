#ifndef REPORT_H
#define REPORT_H

#include "patient.h"
#include "therapist.h"
#include "function.h"

/*
 * Entity class. Holds attributes of a Report.
*/

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
    QList<Function*> getFunctions(Function::Art actArt);

    int getPatientId() const;
    void setPatientId(int value);

    int getTherapistId() const;
    void setTherapistId(int value);

    int getId() const;
    void setId(int value);

    QString getType() const;
    void setType(const QString &value);

private:
    int id;
    int patientId;
    int therapistId;
    QDate date;
    QList<Function*> functions;
    QString freeText;
    QString type;
};

#endif // REPORT_H
