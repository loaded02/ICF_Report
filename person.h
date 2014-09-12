#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person
{
public:
    Person();
    virtual ~Person();
    Person(QString surname);
    QString getSurname() const;
    void setSurname(const QString &value);

    QString getName() const;
    void setName(const QString &value);

private:
    QString surname;
    QString name;
};

#endif // PERSON_H
