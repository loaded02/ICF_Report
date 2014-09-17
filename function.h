#ifndef FUNCTION_H
#define FUNCTION_H

#include <QString>

class Function
{
public:
    enum Art {function, structure, partizipation, context};
    Function();
    QString getId() const;
    void setId(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    int getValue() const;
    void setValue(int value);

    QString getText() const;
    void setText(const QString &value);

    Art getArt() const {
        return art;
    }
    void setArt(const Art &value) {
        art = value;
    }

private:
    QString id;
    QString description;
    int value;
    QString text;
    Art art;
};

#endif // FUNCTION_H
