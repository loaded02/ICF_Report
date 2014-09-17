#include "person.h"

Person::Person()
{
}

Person::~Person()
{

}

Person::Person(QString surname)
    :surname(surname), id(0){

}
QString Person::getSurname() const
{
    return surname;
}

void Person::setSurname(const QString &value)
{
    surname = value;
}
QString Person::getName() const
{
    return name;
}

void Person::setName(const QString &value)
{
    name = value;
}
int Person::getId() const
{
    return id;
}

void Person::setId(int value)
{
    id = value;
}

