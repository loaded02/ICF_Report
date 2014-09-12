#include "function.h"

Function::Function()
{
}
QString Function::getId() const
{
    return id;
}

void Function::setId(const QString &value)
{
    id = value;
}
QString Function::getDescription() const
{
    return description;
}

void Function::setDescription(const QString &value)
{
    description = value;
}
int Function::getValue() const
{
    return value;
}

void Function::setValue(int value)
{
    value = value;
}
QString Function::getText() const
{
    return text;
}

void Function::setText(const QString &value)
{
    text = value;
}
Art Function::getArt() const
{
    return art;
}

void Function::setArt(const Art &value)
{
    art = value;
}





