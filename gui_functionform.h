#ifndef GUI_FUNCTIONFORM_H
#define GUI_FUNCTIONFORM_H

#include <QWidget>
#include <QDebug>
#include <QInputDialog>

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
    void resetInput();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::GUI_FunctionForm *ui;
};

#endif // GUI_FUNCTIONFORM_H
