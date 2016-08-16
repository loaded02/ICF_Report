#include "gui_settings.h"
#include "ui_gui_settings.h"
#include <QFileDialog>
#include <QSettings>

GUI_Settings::GUI_Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUI_Settings)
{
    ui->setupUi(this);
    QSettings settings;
    ui->lineEdit->setText(settings.value("baseDir").toString());
}

GUI_Settings::~GUI_Settings()
{
    delete ui;
}

QString GUI_Settings::getDirectory()
{
    return ui->lineEdit->text();
}

void GUI_Settings::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    ui->lineEdit->setText(dir);
}
