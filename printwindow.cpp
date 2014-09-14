#include "printwindow.h"

PrintWindow::PrintWindow(QDialog *parent)
    :QDialog(parent)
{
}

void PrintWindow::printHtml(const QString &html)
{
    printer.setOrientation(QPrinter::Portrait);
//    printer.setPageMargins(25,25,25,25,QPrinter::Millimeter);
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec()) {
//        QPainter painter(&printer);
        QTextDocument textDocument;
//        textDocument.setDefaultStyleSheet(this->cssTable());
        textDocument.setHtml(this->cssTable() + html);
        textDocument.print(&printer);
    }
}

void PrintWindow::printHeader(const QStringList &entries)
{
    QString html;
    html += "<body>"
            "<table width=\"100%\" cellspacing=\"0\" class=\"header\"><tr><td>"
            "<p align=\"right\">Befundaufnahme: " + entries[0].toHtmlEscaped() + "</p>"
            "<p>Patient: " + entries[1].toHtmlEscaped() + ", Geb.-Datum: " + entries[2].toHtmlEscaped() + "<br>Diagnose: " + entries[3].toHtmlEscaped() + "</p>"
            "<br>"
            "<h1 align=\"center\">" + entries[4].toHtmlEscaped() + "</h1>"
            "<br>"
            "<p>Therapeut: " + entries[5].toHtmlEscaped() + "</p>"
            "</td></tr></table><br>";

    //test
    html += this->printTable(entries);
    html += "</body>";
    this->printHtml(html);
}

QString PrintWindow::printTable(const QStringList &entries)
{
    QString html;
    html += "<table width=\"100%\" cellspacing=\"0\" class=\"tbl\">"
            "<tr>"
            "<th colspan=\"2\"><b>KOERPERFUNKTIONEN</b></th><th width=\"160px\"><table width=\"160px\" class=\"tbl\"><tr><th colspan=\"6\"><b>Schaedigung</b></th><tr><td></td><td>0</td><td>1</td><td>2</td><td>3</td><td>4</td></tr></table></th>"
            "</tr>"
            "</table>";
    html += "<table>"
            "<tr>"
            "<td width=\"64px\">ID#</td><td>Beschreibung</td><td width=\"160px\"><table width=\"160px\"><tr><td><td></td><td></td><td></td><td></td><td>x</td></td></tr></table></td>"
            "</tr>"
            "<tr><td colspan=\"3\"></td></tr>"
            "</table>";
    return html;
}

QString PrintWindow::cssTable()
{
    QString css;
    css =   "<style type=\"text/css\">"
            "body {font-family:Tahoma,Helvetica,sans-serif;}"
//            "h1 { border-bottom:4px double blue; padding-bottom:4px; margin:0px; }"
//            "h2 { border-top:1px solid blue; margin:0px; }"
//            "p { line-height:150%; }"
            "table.header {border-width: 1px;border-style: solid;border-color: black;margin-top: 0px;margin-bottom: 0px;color: black;}"
            "table.header th {border-width:0;border-style:none; border-collapse:collapse;}"
            "table.header td {border-width:0;border-style:none;border-collapse:collapse;}"
            "table.tbl {border-width: 1px;border-style: solid;border-color: black;margin-left:32px; margin-right:32px; empty-cells:show; table-layout:fixed; border-collapse:collapse; text-align:left;color: black;background-color:#E0E0E0;}"
            "table.tbl th {border-width: 1px;border-style: solid;border-color: black;border-collapse:collapse; text-align:left;background-color:#E0E0E0;}"
            "table.tbl td {font-size:1.2em; border-width: 1px;border-style: solid;border-color: black;border-collapse:collapse; text-align:left;background-color:#E0E0E0;}"
            "</style>";
    return css;
}
