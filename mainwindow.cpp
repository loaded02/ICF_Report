#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui_newperson.h"
#include "icfcontroller.h"
#include "gui_showperson.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include "gui_report.h"
#include <QFileDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("ICF_Report");
    QCoreApplication::setApplicationName("ICF_Report");
    QSettings settings;
    QString baseDir = settings.value("baseDir").toString();

    icfController = new ICFController(baseDir);

    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->pushButtonPat,SIGNAL(clicked()),this,SLOT(on_actionManage_Patients_triggered()));
    connect(ui->pushButtonTher,SIGNAL(clicked()),this,SLOT(on_actionManage_Therapists_triggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete icfController;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"About ICF Report", "ICF Report is used to easily create short ICF Reports. It also includes a simple"
                       " patient management system.\nCreated by loaded 2014");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    QMessageBox box;
    box.setWindowTitle("Save before exit?");
    box.setText("Click Yes for Saving current data.");
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setDefaultButton(QMessageBox::Yes);
    int ret = box.exec();
    if (ret == QMessageBox::Yes)
        icfController->save();
    event->accept();
}

void MainWindow::on_actionSave_All_triggered()
{
    icfController->save();
}

void MainWindow::on_actionManage_Therapists_triggered()
{
    GUI_ShowPerson* form = new GUI_ShowPerson(icfController,'t',this);
    form->setWindowTitle("Manage Therapists");
    form->exec();
    delete form;
}

void MainWindow::on_actionManage_Patients_triggered()
{
    GUI_ShowPerson* form = new GUI_ShowPerson(icfController,'p',this);
    form->setWindowTitle("Manage Patients");
    form->exec();
    delete form;
}

void MainWindow::on_pushButtonrepNew_clicked()
{
    GUI_Report* repForm = new GUI_Report(icfController,this);
    repForm->exec();
    delete repForm;
}

void MainWindow::on_pushButtonRep_clicked()
{

}

void MainWindow::on_actionSet_Xml_Directory_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    QSettings settings;
    settings.setValue("baseDir",dir);
}
