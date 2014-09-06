#include "patient.h"

Patient::Patient()
{

}

Patient::Patient(QString surname)
    :surname(surname)
{
}
QString Patient::getSurname() const
{
    return surname;
}

void Patient::setSurname(const QString &value)
{
    surname = value;
}
QString Patient::getName() const
{
    return name;
}

void Patient::setName(const QString &value)
{
    name = value;
}
QString Patient::getDiagnosis() const
{
    return diagnosis;
}

void Patient::setDiagnosis(const QString &value)
{
    diagnosis = value;
}
QDate Patient::getDob() const
{
    return dob;
}

void Patient::setDob(const QDate &value)
{
    dob = value;
}




