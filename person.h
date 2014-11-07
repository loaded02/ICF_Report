#ifndef PERSON_H
#define PERSON_H

#include <QString>

/*
 * Entity class. Holds attributes of a Person.
*/

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

    int getId() const;
    void setId(int value);

private:
    int id;
    QString surname;
    QString name;
};

#endif // PERSON_H
