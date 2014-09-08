#ifndef PARTIZIPATION_H
#define PARTIZIPATION_H

#include <QString>

class Partizipation
{
public:
    Partizipation();
    QString getId() const;
    void setId(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    int getValue() const;
    void setValue(int value);

    QString getText() const;
    void setText(const QString &value);

private:
    QString id;
    QString description;
    int value;
    QString text;
};

#endif // PARTIZIPATION_H
