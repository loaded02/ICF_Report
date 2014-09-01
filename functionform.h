#ifndef FUNCTIONFORM_H
#define FUNCTIONFORM_H

#include <QWidget>

namespace Ui {
class FunctionForm;
}

class FunctionForm : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionForm(QWidget *parent = 0);
    ~FunctionForm();
    void setLabel(QString text);

private:
    Ui::FunctionForm *ui;
};

#endif // FUNCTIONFORM_H
