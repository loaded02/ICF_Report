#ifndef PATIENT_H
#define PATIENT_H

#include <QDate>
#include "person.h"

class Patient : public Person
{
public:
    Patient();
    virtual ~Patient();
    Patient(QString surname);

    QString getDiagnosis() const;
    void setDiagnosis(const QString &value);

    QDate getDob() const;
    void setDob(const QDate &value);

private:
    QString diagnosis;
    QDate dob;
};

#endif // PATIENT_H
