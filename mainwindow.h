#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <ui_mainwindow.h>
#include "newpersonform.h"
#include "icfcontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_cancelButton_clicked();

    void on_actionAbout_triggered();

    void on_actionNew_Therapist_triggered();

    void on_actionNew_Patient_triggered();

    void on_saveButton_clicked();

private:
    void fillTherComboBox();
    void fillPatComboBox();
    Ui::MainWindow *ui;
    ICFController* icfController;
};

#endif // MAINWINDOW_H
