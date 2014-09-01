#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
