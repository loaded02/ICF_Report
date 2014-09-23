#ifndef GUI_SHOWPERSON_H
#define GUI_SHOWPERSON_H

#include <QDialog>
#include <QListWidgetItem>
#include "gui_newperson.h"
#include "mainwindow.h"
#include "icfcontroller.h"

namespace Ui {
class GUI_ShowPerson;
}

class GUI_ShowPerson : public QDialog
{
    Q_OBJECT

public:
    explicit GUI_ShowPerson(ICFController* controller, char art, QWidget *parent = 0);
    ~GUI_ShowPerson();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_closeButton_clicked();

    void on_editButton_clicked();

    void on_removeButton_clicked();

    void on_refreshButton_clicked();

private:
    void fillListView();
    Ui::GUI_ShowPerson *ui;
    ICFController* icfcontroller;
    char art;
};

#endif // GUI_SHOWPERSON_H
