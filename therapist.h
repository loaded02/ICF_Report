#ifndef THERAPIST_H
#define THERAPIST_H

#include "person.h"

/*
 * Entity class. Holds attributes of a Therapist.
*/

class Therapist : public Person
{
public:
    Therapist();
    virtual ~Therapist();
    Therapist(QString surname);

    QString getCompany() const;
    void setCompany(const QString &value);

private:
    QString company;
};

#endif // THERAPIST_H
