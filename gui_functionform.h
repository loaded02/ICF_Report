#ifndef GUI_FUNCTIONFORM_H
#define GUI_FUNCTIONFORM_H

#include <QWidget>

namespace Ui {
class GUI_FunctionForm;
}

class GUI_FunctionForm : public QWidget
{
    Q_OBJECT

public:
    explicit GUI_FunctionForm(QWidget *parent = 0);
    ~GUI_FunctionForm();
    void setLabel(QString text);
    bool isChecked();
    int getValue();
    QString getDescription();
    QString getId();
    QString getText();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::GUI_FunctionForm *ui;
};

#endif // GUI_FUNCTIONFORM_H
