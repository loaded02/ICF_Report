#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <ui_mainwindow.h>
#include <QCloseEvent>
#include "gui_newperson.h"
#include "icfcontroller.h"
#include "gui_showperson.h"
#include "function.h"

/*MainWindow is called from main(..). It is the mainframe and shows just the header with
* 2 comboboxes and dateedit and the footer with buttons like print, save, etc. The central
* 3 widgets are designed in GUI_FunctionForm and GUI_Function. The Businesslogic is controlled
* and encapsulated by ICFController. This class is instanciated by MainWindow. */

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
    /*Clears all forms that are currently shown*/
    void clearForm();
    /*Connect Signals to Slots in MainWindow and to GUI_Functionform*/
    void connectSignals();
    /*Subfunction for ConnectSignals()*/
    void connectLoop(QList<GUI_FunctionForm*> list);
signals:
    void changeDescription(QString value, int rnd);
    void addIcfCodeToForm(QString value);

public slots:
    void on_actionNew_Therapist_triggered();

    void on_actionNew_Patient_triggered();

    void closeEvent(QCloseEvent * event);

    void icfIdChanged(QString icfId, int rnd);

private slots:
    void on_cancelButton_clicked();

    void on_actionAbout_triggered();

    void on_saveButton_clicked();

    void on_printButton_clicked();

    void on_actionManage_Therapists_triggered();

    void on_actionManage_Patients_triggered();

    void on_reportcB_currentIndexChanged(const QString &arg1);

    void on_patientcB_currentIndexChanged(const QString &arg1);

    void on_deleteButton_clicked();

    void on_actionSave_All_triggered();

private:
    void saveFunctionAttributes(Report* rep, QList<GUI_FunctionForm *> list, Function::Art art);
    void saveReport();
    void fillTherComboBox();
    void fillPatComboBox();
    void addPatient(QString surname, QString name, QDate dob, QString diagnosis);
    void addTherapist(QString surname, QString name);
    void fillReportForm(Report* rep);
    Ui::MainWindow *ui;
    ICFController* icfController;
    int currentReportId;
};

#endif // MAINWINDOW_H
