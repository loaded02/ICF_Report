#include "report.h"

Report::Report(QDate date)
    :date(date)
{
}

Report::~Report() {}

Patient Report::getPatient() const
{
    return patient;
}

void Report::setPatient(const Patient &value)
{
    patient = value;
}
Therapist Report::getTherapist() const
{
    return therapist;
}

void Report::setTherapist(const Therapist &value)
{
    therapist = value;
}
QDate Report::getDate() const
{
    return date;
}

void Report::setDate(const QDate &value)
{
    date = value;
}



