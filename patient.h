#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QDate>

class Patient
{
public:
    Patient();
    Patient(QString surname);
    QString getSurname() const;
    void setSurname(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getDiagnosis() const;
    void setDiagnosis(const QString &value);

    QDate getDob() const;
    void setDob(const QDate &value);

private:
    QString surname;
    QString name;
    QString diagnosis;
    QDate dob;
};

#endif // PATIENT_H
