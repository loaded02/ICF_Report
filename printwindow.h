#ifndef PRINTWINDOW_H
#define PRINTWINDOW_H

#include <QDialog>
#include "report.h"
#include "icfcontroller.h"

/*
 * Uses QTextDocument to print given report data onto a printer or pdf file.
 * Layout of the page is set here.
*/

class ICFController;

class PrintWindow : public QDialog
{
    Q_OBJECT
public:
    PrintWindow(ICFController* icfController, QDialog *parent = 0);
    ~PrintWindow();
    int printReport(int repId);
private:
    void createXmlReport(Report &rep);
    void createXmlTherapist(Report &rep, QDomDocument &doc, QDomElement &root);
    void createXmlPatient(Report &rep, QDomDocument &doc, QDomElement &root);
    void createXmlFunction(Report& rep, QDomDocument& doc, QDomElement& root);
    ICFController* icfController;
};

#endif // PRINTWINDOW_H
