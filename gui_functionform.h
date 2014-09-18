#ifndef GUI_FUNCTIONFORM_H
#define GUI_FUNCTIONFORM_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class GUI_FunctionForm;
}

class GUI_FunctionForm : public QWidget
{
    Q_OBJECT

public:
    explicit GUI_FunctionForm(QWidget *parent = 0);
    ~GUI_FunctionForm();
    void setDescription(QString text);
    bool isChecked();
    int getValue();
    void setValue(int val);
    QString getDescription();
    QString getId();
    void setId(QString id);
    QString getText();
    void setText(QString txt);

private:
    Ui::GUI_FunctionForm *ui;
};

#endif // GUI_FUNCTIONFORM_H
