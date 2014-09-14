#ifndef GUI_SHOWPERSON_H
#define GUI_SHOWPERSON_H

#include <QDialog>
#include <QListWidgetItem>
#include "icfcontroller.h"
#include "gui_newperson.h"

namespace Ui {
class GUI_ShowPerson;
}

class GUI_ShowPerson : public QDialog
{
    Q_OBJECT

public:
    explicit GUI_ShowPerson(QList<Person *>* persons, QWidget *parent = 0);
    ~GUI_ShowPerson();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    void fillListView();
    Ui::GUI_ShowPerson *ui;
    QList<Person*>* persons;
};

#endif // GUI_SHOWPERSON_H
