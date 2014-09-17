#ifndef GUI_FUNCTION_H
#define GUI_FUNCTION_H

#include <QWidget>
#include "gui_functionform.h"

namespace Ui {
class GUI_Function;
}

class GUI_Function : public QWidget
{
    Q_OBJECT

public:
    explicit GUI_Function(QWidget *parent = 0);
    ~GUI_Function();
    void hideUnit(int pos);
    void setLabel(QString text);
    static int NoFunctions;
    QList<GUI_FunctionForm*> getActiveWidgets();

private slots:
    void on_addButton_clicked();

    void on_removeButton_clicked();

private:
    Ui::GUI_Function *ui;
};

#endif // GUI_FUNCTION_H