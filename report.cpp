#include "report.h"

Report::Report(QDate date)
    :date(date),id(0)
{
}

Report::~Report() {}

QDate Report::getDate() const
{
    return date;
}

void Report::setDate(const QDate &value)
{
    date = value;
}
QString Report::getFreeText() const
{
    return freeText;
}

void Report::setFreeText(const QString &value)
{
    freeText = value;
}
int Report::getPatientId() const
{
    return patientId;
}

void Report::setPatientId(int value)
{
    patientId = value;
}
int Report::getTherapistId() const
{
    return therapistId;
}

void Report::setTherapistId(int value)
{
    therapistId = value;
}
int Report::getId() const
{
    return id;
}

void Report::setId(int value)
{
    id = value;
}







