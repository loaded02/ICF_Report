#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>
#include <QCloseEvent>
#include "icfcontroller.h"


/*
 * MainWindow is called from main(..). It is the mainframe and shows just the header with
 * 2 comboboxes and dateedit and the footer with buttons like print, save, etc. The central
 * 3 widgets are designed in GUI_FunctionForm and GUI_Function. The Businesslogic is controlled
 * and encapsulated by ICFController. ICFController is instanciated by MainWindow.
*/

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*Default Constructor*/
    explicit MainWindow(QWidget *parent = 0);
    /*Destructor*/
    ~MainWindow();

private slots:
    void closeEvent(QCloseEvent * event);
    void on_actionAbout_triggered();
    void on_actionSave_All_triggered();
    void on_pushButtonrepNew_clicked();
    void on_pushButtonRep_clicked();
    void on_actionManage_Therapists_triggered();
    void on_actionManage_Patients_triggered();

private:
    Ui::MainWindow *ui;
    ICFController* icfController;
};

#endif // MAINWINDOW_H
