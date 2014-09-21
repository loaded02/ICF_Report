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
        html += this->printTable(report->getFunctions(Function::function));
        html += this->printTable(report->getFunctions(Function::structure));
        html += this->printTable(report->getFunctions(Function::partizipation));
        html += this->printTable(report->getFunctions(Function::context));
        html += this->printText(report->getFreeText());
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

QString PrintWindow::printTable(const QList<Function *>func)
{
    if (func.isEmpty()) return "";
    QString art;
    switch (func.at(0)->getArt()) {
    case Function::function : art = "KOERPERFUNKTIONEN";
        break;
    case Function::structure : art = "KOERPERSTRUKTUREN";
        break;
    case Function::partizipation : art = "PARTIZIPATION";
        break;
    case Function::context : art = "KONTEXTFAKTOREN";
        break;
    default:;
    }

    QString html;
    html += "<table width=\"100%\" cellspacing=\"0\" class=\"tbl\">"
            "<tr>"
            "<th rowspan=\"2\" colspan=\"2\" align=\"left\"><b>" + art + "</b></th><th colspan=\"6\" align=\"left\"><b>Schaedigung</b></th>"
            "</tr>"
            "<tr>"
            "<th></th><th>0</th><th>1</th><th>2</th><th>3</th><th>4</th>"
            "</tr>";
    foreach ( Function* actFunc, func) {
        QString null, one, two, three, four;
        switch (actFunc->getValue()) {
        case 0 : null="x";
            break;
        case 1 : one ="x";
            break;
        case 2 : two = "x";
            break;
        case 3 : three = "x";
            break;
        case 4 : four = "x";
            break;
        default: ;
        }

        html += "<tr>"
                "<td width=\"7%\" rowspan=\"2\">" + actFunc->getId() + "</td><td width=\"63%\" rowspan=\"2\">" + actFunc->getDescription() + "</td><td>LF</td><td align=\"center\">"
                + null + "</td><td align=\"center\">" + one + "</td><td align=\"center\">" + two + "</td><td align=\"center\">" + three + "</td><td align=\"center\">" + four + "</td>"
                "</tr>"
                "<tr>"
                "<td>L</td><td align=\"center\">" + null + "</td><td align=\"center\">" + one + "</td><td align=\"center\">" + two + "</td><td align=\"center\">" + three + "</td><td align=\"center\">" + four + "</td>"
                "</tr>"
                "<tr><td colspan=\"8\">" + actFunc->getText() + "</td></tr>";
    }
    html += "</table><br>";
    return html;
}

QString PrintWindow::printText(QString txt)
{
    txt = "<br><br><p>" + txt + "</p><br><br>";
    return txt;
}

QString PrintWindow::printFooter(const Report *report)
{
    QString html;
    html += "<p>Praxis :" + QString::number(report->getTherapistId()) + "</p>";
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
