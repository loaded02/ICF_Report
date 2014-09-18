#include "report.h"

Report::Report(QDate date)
    :id(0),date(date)
{
}

Report::~Report() {
    foreach(Function* func, functions) {
        delete func;
    }
}

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







