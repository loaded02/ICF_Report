#ifndef GUI_FUNCTION_H
#define GUI_FUNCTION_H

#include <QWidget>
#include "gui_functionform.h"

/*
 * View class. Shows 2 buttons and up to 10 widgets, which are
 * GUI_FunctionForm classes. This QWidget is used in Mainwindow.
*/

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
    void hideAll();
    GUI_FunctionForm* setUnitVisible();
    void setLabel(QString text);
    static int NoFunctions;
    QList<GUI_FunctionForm*> getActiveWidgets();
    QList<GUI_FunctionForm*> getAllWidgets();

private slots:
    void on_addButton_clicked();

    void on_removeButton_clicked();

private:
    Ui::GUI_Function *ui;
};

#endif // GUI_FUNCTION_H
