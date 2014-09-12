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

private:
    Patient patient;
    Therapist therapist;
    QDate date;
};

#endif // REPORT_H
