#ifndef NEWPATIENTFORM_H
#define NEWPATIENTFORM_H

#include <QDialog>

namespace Ui {
class NewPatientForm;
}

class NewPatientForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewPatientForm(QWidget *parent = 0);
    ~NewPatientForm();

private:
    Ui::NewPatientForm *ui;
};

#endif // NEWPATIENTFORM_H
