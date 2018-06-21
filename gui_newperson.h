#ifndef GUI_NEWPERSON_H
#define GUI_NEWPERSON_H

#include <QDialog>

/*
 * View class. Dialog with Person attributes.
 * Used to insert a new Person.
*/

namespace Ui {
class GUI_NewPerson;
}

class GUI_NewPerson : public QDialog
{
    Q_OBJECT

public:
    explicit GUI_NewPerson(QWidget *parent = 0);
    ~GUI_NewPerson();
    void therapistAppearance();
    void setSurname(QString surname);
    QString getSurname();
    void setName(QString name);
    QString getName();
    void setDob(QDate dob);
    QDate getDob();
    void setDiagnosis(QString diagnosis);
    QString getDiagnosis();

private:
    void hideDob();
    void hideDiagnosis();
    Ui::GUI_NewPerson *ui;
};

#endif // GUI_NEWPERSON_H
