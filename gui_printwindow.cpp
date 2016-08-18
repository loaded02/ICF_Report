#include "gui_printwindow.h"
#include "ui_gui_printwindow.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QProcess>

GUI_PrintWindow::GUI_PrintWindow(ICFController *icfController, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUI_PrintWindow),
    icfController(icfController)
{
    ui->setupUi(this);
    //make cmd
    QProcess *process = new QProcess();
    process->setWorkingDirectory(icfController->getBaseDir());
    connect(process, SIGNAL(finished(int)), this, SLOT(onProcessFinished(int)));
    process->start("make", QStringList() << "html");
}

GUI_PrintWindow::~GUI_PrintWindow()
{
    delete ui;
}

void GUI_PrintWindow::accept()
{
    QPrinter printer;
    printer.setOutputFileName("report.pdf");
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    QPrintDialog printDialog(&printer, this);
    printDialog.setWindowTitle(tr("Print Document"));
    if (printDialog.exec() == QDialog::Accepted) {
        ui->webView->print(&printer);
    }
    QDialog::accept();
}

void GUI_PrintWindow::onProcessFinished(int status)
{
    if (!status)
        ui->webView->load(QUrl::fromLocalFile(icfController->getBaseDir() + "/report.xml"));
}
