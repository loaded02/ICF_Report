#ifndef GUI_SETTINGS_H
#define GUI_SETTINGS_H

#include <QDialog>

namespace Ui {
class GUI_Settings;
}

class GUI_Settings : public QDialog
{
    Q_OBJECT

public:
    explicit GUI_Settings(QWidget *parent = 0);
    ~GUI_Settings();
    QString getDirectory();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GUI_Settings *ui;
};

#endif // GUI_SETTINGS_H
