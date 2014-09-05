#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ICF Report");
    //show 3 forms at startup
    for (int i = 4; i < 11; ++i) {
        ui->functionsWidget->hideUnit(i);
        ui->structuresWidget->hideUnit(i);
        ui->partizipationWidget->hideUnit(i);
    }
    ui->structuresWidget->setLabel("Körperstrukturen");
    ui->partizipationWidget->setLabel("Partizipation");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cancelButton_clicked()
{
    this->setVisible(false);
    exit(0);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"About ICF Report", "ICF Report is used to easily create short ICF Reports. It also includes a simple"
                       " patient management system.\nCreated by loaded 2014");
}

void MainWindow::on_actionNew_Therapist_triggered()
{
    QString therapist = QInputDialog::getText(this, "Enter Therapist Name", QString::null,QLineEdit::Normal,"Enter Therapist Name");
    ui->therapeutcB->addItem(therapist);
}

void MainWindow::on_actionNew_Patient_triggered()
{
    NewPatientForm* patient = new NewPatientForm();
    patient->show();
}
