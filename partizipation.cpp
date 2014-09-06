#include "partizipation.h"

Partizipation::Partizipation()
{
}
QString Partizipation::getId() const
{
    return id;
}

void Partizipation::setId(const QString &value)
{
    id = value;
}
QString Partizipation::getDescription() const
{
    return description;
}

void Partizipation::setDescription(const QString &value)
{
    description = value;
}
int Partizipation::getValue() const
{
    return value;
}

void Partizipation::setValue(int value)
{
    value = value;
}
QString Partizipation::getText() const
{
    return text;
}

void Partizipation::setText(const QString &value)
{
    text = value;
}




