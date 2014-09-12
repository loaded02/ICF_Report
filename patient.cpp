#include "patient.h"

Patient::Patient()
    :Person(){

}

Patient::~Patient()
{


}

Patient::Patient(QString surname)
    :Person(surname)
{
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




