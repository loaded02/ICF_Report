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

QList<Function *> Report::getFunctions(Function::Art actArt)
{
    QList<Function*> result;
    foreach (Function* func, functions) {
        if (func->getArt() == actArt) {
            result.append(func);
        }
    }
    return result;
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

QString Report::getType() const
{
    return type;
}

void Report::setType(const QString &value)
{
    type = value;
}







