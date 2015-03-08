#include "therapist.h"

Therapist::Therapist()
    :Person(){

}

Therapist::~Therapist()
{

}

Therapist::Therapist(QString surname)
    :Person(surname)
{
}
QString Therapist::getCompany() const
{
    return company;
}

void Therapist::setCompany(const QString &value)
{
    company = value;
}




