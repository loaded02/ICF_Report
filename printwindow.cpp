#include "printwindow.h"

PrintWindow::PrintWindow(QDialog *parent)
    :QDialog(parent)
{
}

void PrintWindow::printHtml(const QString &html)
{
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec()) {
//        QPainter painter(&printer);
        QTextDocument textDocument;
        textDocument.setDefaultStyleSheet(this->cssTable());
        textDocument.setHtml(html);
        textDocument.print(&printer);
    }
}

void PrintWindow::printHeader(const QStringList &entries)
{
    QString html;
    html += "<body>"
            "<div id=\"header\">"
            "<p align=\"right\">Befundaufnahme: " + entries[0].toHtmlEscaped() + "</p>"
            "<p>Patient: " + entries[1].toHtmlEscaped() + ", Geb.-Datum: " + entries[2].toHtmlEscaped() + "<br>Diagnose: " + entries[3].toHtmlEscaped() + "</p>"
            "<br>"
            "<h1 align=\"center\">" + entries[4].toHtmlEscaped() + "</h1>"
            "<br>"
            "<p>Therapeut: " + entries[5].toHtmlEscaped() + "</p>"
            "</div>"
            "<br>";

    //test
    html += "bla</body>";
    this->printHtml(html);
}

QString PrintWindow::cssTable()
{
    QString css;
    css =   "<style type=\"text/css\">"
            "* {"
            "  margin: 0;"
            "  padding: 0;"
            "}"
            "body {margin:2.5cm 2.5cm 2.0cm 2.5cm; width: 21cm;}"
            "h1 { border-bottom:4px double blue; padding-bottom:4px; margin:0px; }"
            "h2 { border-top:1px solid blue; margin:0px; }"
            "p { line-height:150%; }"
            "p.info { border:1px solid gray; background-color:#E0E0E0; padding:4px; margin:0px; }"
            "span.rahmen { border:2px solid red; }"
            "div#header { border: 2px solid black;}"
            "#header h1 {border: 0;}"
            "div#tableHeader {}"
            "#tableHeader table {width:19cm; border:1px solid black; margin-left:1cm; margin-right:1cm; empty-cells:show; table-layout:fixed; border-collapse:collapse; text-align:left; background-color:#E0E0E0;}"
            "body { font-family:Tahoma,Helvetica,sans-serif; }"
            "table {width:19cm; border:1px solid black; margin-left:1cm; margin-right:1cm; empty-cells:show; table-layout:fixed; border-collapse:collapse; text-align:left;}"
            "th {border:1px solid black; border-collapse:collapse; text-align:left;}"
            "td {font-size:1.2em; border:1px solid black; border-collapse:collapse; text-align:left;}"
            "</style>";
    return css;
}
