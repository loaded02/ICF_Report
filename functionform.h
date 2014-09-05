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
    bool isChecked();
    int getValue();
    QString getDescription();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::FunctionForm *ui;
};

#endif // FUNCTIONFORM_H
