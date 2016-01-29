#ifndef GUI_REPORT_H
#define GUI_REPORT_H

#include <QDialog>
#include "icfcontroller.h"
#include "function.h"
#include "gui_functionform.h"

namespace Ui {
class GUI_Report;
}

class GUI_Report : public QDialog
{
    Q_OBJECT

public:
    explicit GUI_Report(ICFController* icfController, QWidget *parent = 0);
    ~GUI_Report();

signals:
    void changeDescription(QString value, int rnd);
    void addIcfCodeToForm(QString value);

public slots:
    void icfIdChanged(QString icfId, int rnd);

    void on_patientcB_currentIndexChanged(const QString &arg1);

    void on_therapeutcB_currentIndexChanged(const QString &arg1);

    void on_reportcB_currentIndexChanged(const QString &arg1);

    void on_cancelButton_clicked();

    void on_deleteButton_clicked();

    void on_printButton_clicked();

    void on_saveButton_clicked();

private:
    /*Clears all forms that are currently shown*/
    void clearForm();
    /*Connect Signals to Slots in MainWindow and to GUI_Functionform*/
    void connectSignals();
    /*Subfunction for ConnectSignals()*/
    void connectLoop(QList<GUI_FunctionForm*> list);
    void saveFunctionAttributes(Report* rep, QList<GUI_FunctionForm *> list, Function::Art art);
    void saveReport();
    void fillTherComboBox();
    void fillPatComboBox();
    void fillReportForm(Report* rep);
    Ui::GUI_Report *ui;
    ICFController* m_icfController;
    int currentReportId;
};

#endif // GUI_REPORT_H
