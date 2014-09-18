#ifndef PRINTWINDOW_H
#define PRINTWINDOW_H

#include <QString>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QDebug>
#include "report.h"
#include "icfcontroller.h"

class ICFController;

class PrintWindow : public QDialog
{
    Q_OBJECT
public:
    PrintWindow(ICFController* icfController, QDialog *parent = 0);
    ~PrintWindow();
    void printReport(int repId);
private:
    void printHtml(const QString &html);
    QString printHeader(const Report *report);
    QString printTable(const Function *func);
    QString printText(QString txt);
    QString printFooter(const Report *report);
    QString cssTable();
    QPrinter printer;
    ICFController* icfController;
};

#endif // PRINTWINDOW_H
