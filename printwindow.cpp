#include "printwindow.h"

PrintWindow::PrintWindow(ICFController* icfController, QDialog *parent)
    :QDialog(parent), icfController(icfController)
{
}

PrintWindow::~PrintWindow()
{

}

void PrintWindow::printReport(int repId)
{
    Report* report;
    if ((report = icfController->findReport(repId))) {
        QString html;
        html += this->printHeader(report);
        for (int i=0; i<report->sizeOfFunctions(); i++) {
            html += this->printTable(report->getFunction(i))+ "<br>";
        }
        html += this->printFooter(report);
        this->printHtml(html);
    }
}

void PrintWindow::printHtml(const QString &html)
{
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec()) {
//        QPainter painter(&printer);
        QTextDocument textDocument;
//        textDocument.setDefaultStyleSheet(this->cssTable());
        textDocument.setHtml(this->cssTable() + html);
        textDocument.print(&printer);
    }
}

QString PrintWindow::printHeader(const Report* report)
{
    Patient* pat = icfController->findPatient(report->getPatientId());
    Therapist* ther = icfController->findTherapist(report->getTherapistId());
    QString html;
    html += "<body>"
            "<table width=\"100%\" cellspacing=\"0\" class=\"header\"><tr><td>"
            "<p align=\"right\">Befundaufnahme: " + report->getDate().toString().toHtmlEscaped() + "</p>"
            "<p>Patient: " + pat->getName().toHtmlEscaped() + " " + pat->getSurname().toHtmlEscaped() +
            ", Geb.-Datum: " + pat->getDob().toString().toHtmlEscaped() + "<br>Diagnose: " + pat->getDiagnosis().toHtmlEscaped() + "</p>"
            "<h1 align=\"center\">" + "ICF Core Set - Apoplex" + "</h1>"
            "<p>Therapeut: " + ther->getName().toHtmlEscaped() + " " + ther->getSurname().toHtmlEscaped() + "</p>"
            "</td></tr></table><br>";
    return html;
}

QString PrintWindow::printTable(const Function *func)
{
    QString html;
    html += "<table width=\"100%\" cellspacing=\"0\" class=\"tbl\">"
            "<tr>"
            "<th rowspan=\"2\" colspan=\"2\" align=\"left\"><b>KOERPERFUNKTIONEN</b></th><th colspan=\"6\" align=\"left\"><b>Schaedigung</b></th>"
            "</tr>"
            "<tr>"
            "<th></th><th>0</th><th>1</th><th>2</th><th>3</th><th>4</th>"
            "</tr>";
    html += "<tr>"
            "<td width=\"7%\" rowspan=\"2\">ID#</td><td width=\"63%\" rowspan=\"2\">Beschreibung</td><td>LF</td><td>"
            "</td><td></td><td></td><td align=\"center\">x</td><td></td>"
            "</tr>"
            "<tr>"
            "<td>L</td><td></td><td></td><td></td><td align=\"center\">x</td><td></td>"
            "</tr>";
    html += "</table>";
    return html;
}

QString PrintWindow::printText(QString txt)
{
    txt += "<br><br><p>Hier kommt der Freitext.</p><br><br>";
    return txt;
}

QString PrintWindow::printFooter(const Report *report)
{
    QString html;
    html += "<p>Praxis für Physiotherapie XYZ</p>";
    html += "</body>";
    return html;
}

QString PrintWindow::cssTable()
{
    QString css;
    css =   "<style type=\"text/css\">"
            "body {font-family:Tahoma,Helvetica,sans-serif;}"
            "p {margin-top: 10px;margin-right:10px;margin-bottom:10px;margin-left:10px;}"
            "table.header {border-width: 1px;border-style: solid;border-color: black;color: black;}"
            "table.header th {border-width:0;border-style:none;border-collapse:collapse;}"
            "table.header td {border-width:0;border-style:none;border-collapse:collapse;}"
            "table.tbl {border-width: 1px;border-style: solid;border-color: black;margin-left:32px; margin-right:32px; empty-cells:show; table-layout:fixed; border-collapse:collapse; text-align:left;color: black;background-color:#E0E0E0;}"
            "table.tbl th {border-width: 1px;border-style: solid;border-color: black;border-collapse:collapse; text-align:left;background-color:#E0E0E0;}"
            "table.tbl td {border-width: 1px;border-style: solid;border-color: black;border-collapse:collapse; text-align:left;background-color:#FFFFFF;}"
            "</style>";
    return css;
}
