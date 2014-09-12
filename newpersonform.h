#ifndef NEWPERSONFORM_H
#define NEWPERSONFORM_H

#include <QDialog>

namespace Ui {
class NewPersonForm;
}

class NewPersonForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewPersonForm(QWidget *parent = 0);
    ~NewPersonForm();
    void hideDob();
    void hideDiagnosis();

private:
    Ui::NewPersonForm *ui;
};

#endif // NEWPERSONFORM_H
