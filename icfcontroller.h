#ifndef ICFCONTROLLER_H
#define ICFCONTROLLER_H

#include "report.h"
#include "patient.h"
#include "therapist.h"

class ICFController
{
public:
    ICFController();
private:
    QList reports;
};

#endif // ICFCONTROLLER_H
