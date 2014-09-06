#include "therapist.h"

Therapist::Therapist()
{

}

Therapist::Therapist(QString surname)
    :surname(surname)
{
}
QString Therapist::getSurname() const
{
    return surname;
}

void Therapist::setSurname(const QString &value)
{
    surname = value;
}
QString Therapist::getName() const
{
    return name;
}

void Therapist::setName(const QString &value)
{
    name = value;
}


