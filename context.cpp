#include "context.h"

Context::Context()
{
}
QString Context::getId() const
{
    return id;
}

void Context::setId(const QString &value)
{
    id = value;
}
QString Context::getDescription() const
{
    return description;
}

void Context::setDescription(const QString &value)
{
    description = value;
}
int Context::getValue() const
{
    return value;
}

void Context::setValue(int value)
{
    value = value;
}
QString Context::getText() const
{
    return text;
}

void Context::setText(const QString &value)
{
    text = value;
}




