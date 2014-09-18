#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include <QDebug>
#include <ui_mainwindow.h>
#include <QCloseEvent>
#include "gui_newperson.h"
#include "icfcontroller.h"
#include "gui_showperson.h"
#include "function.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void on_actionNew_Therapist_triggered();

    void on_actionNew_Patient_triggered();

    void closeEvent(QCloseEvent * event);

private slots:
    void on_cancelButton_clicked();

    void on_actionAbout_triggered();

    void on_saveButton_clicked();

    void on_printButton_clicked();

    void on_actionManage_Therapists_triggered();

    void on_actionManage_Patients_triggered();

    void on_reportcB_currentIndexChanged(const QString &arg1);

    void on_patientcB_currentIndexChanged(const QString &arg1);

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
