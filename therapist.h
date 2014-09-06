#ifndef THERAPIST_H
#define THERAPIST_H

#include <QString>

class Therapist
{
public:
    Therapist();
    Therapist(QString surname);

    QString getSurname() const;
    void setSurname(const QString &value);

    QString getName() const;
    void setName(const QString &value);

private:
    QString surname;
    QString name;
};

#endif // THERAPIST_H
