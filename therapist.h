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
};

#endif // THERAPIST_H
