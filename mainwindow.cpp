#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui_newperson.h"
#include "icfcontroller.h"
#include "gui_showperson.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include "gui_report.h"
#include <QSettings>
#include <QPixmap>
#include "gui_settings.h"

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
    connect(ui->pushButtonRepNew,SIGNAL(clicked(bool)),this,SLOT(on_actionManage_Reports_triggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete icfController;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox box(QMessageBox::Question, "About ICF Report", "ICF Report is used to easily create short ICF Reports. It also includes a simple"
                                        " patient management system.\nCreated by loaded 2014");
    box.setIconPixmap(QPixmap(":/Built_with_Qt_RGB_logo_vertical.png"));
    box.resize(600, 300);
    box.exec();
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

void MainWindow::on_actionSet_Xml_Directory_triggered()
{
    GUI_Settings dialog;
    if (dialog.exec()) {
        QSettings settings;
        settings.setValue("baseDir",dialog.getDirectory());
        QMessageBox box;
        box.setText("Settings saved.");
        box.exec();
    }
}

void MainWindow::on_actionManage_Reports_triggered()
{
    GUI_Report* repForm = new GUI_Report(icfController,this);
    repForm->exec();
    delete repForm;
}
