#ifndef THERAPIST_H
#define THERAPIST_H

#include "person.h"

class Therapist : public Person
{
public:
    Therapist();
    virtual ~Therapist();
    Therapist(QString surname);
};

#endif // THERAPIST_H
