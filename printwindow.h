#ifndef PRINTWINDOW_H
#define PRINTWINDOW_H

#include <QString>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextDocument>

class PrintWindow : public QDialog
{
    Q_OBJECT
public:
    PrintWindow(QDialog *parent = 0);
    void printHtml(const QString &html);
    void printHeader(const QStringList &entries);
    QString printTable(const QStringList &entries);
private:
    QString cssTable();
    QPrinter printer;
};

#endif // PRINTWINDOW_H
