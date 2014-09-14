#include "gui_showperson.h"
#include "ui_gui_showperson.h"

void GUI_ShowPerson::fillListView()
{
    ui->listWidget->clear();
    foreach (Person* actPerson, *persons) {
        new QListWidgetItem(actPerson->getName() + " " + actPerson->getSurname(),ui->listWidget);
    }
}

GUI_ShowPerson::GUI_ShowPerson(QList<Person *> *persons, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUI_ShowPerson),persons(persons){
    ui->setupUi(this);
    this->fillListView();
}

GUI_ShowPerson::~GUI_ShowPerson()
{
    delete ui;
}

void GUI_ShowPerson::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QStringList stringList = item->text().split(" ");
    int i;
    bool exists = false;
    for (i=0; i<persons->size(); i++) {
        if (persons->at(i)->getSurname() == stringList[1]) {
            exists = true;
            break;
        }
    }
    if (!exists) return;
    Person* actPerson = persons->at(i);
    GUI_NewPerson* form = new GUI_NewPerson(this);
    form->setSurname(actPerson->getSurname());
    form->setName(actPerson->getName());
    Therapist* ther = dynamic_cast<Therapist*>(actPerson);
    Patient* pat = dynamic_cast<Patient*>(actPerson);
    if (ther) {
        form->therapistAppearance();
        form->setWindowTitle("Edit Therapist");
        if (form->exec()) {
            ther->setSurname(form->getSurname());
            ther->setName(form->getName());
        }
    }
    if (pat) {
        form->setDob(pat->getDob());
        form->setDiagnosis(pat->getDiagnosis());
        form->setWindowTitle("Edit Patient");
        if (form->exec()) {
            pat->setSurname(form->getSurname());
            pat->setName(form->getName());
            pat->setDob(form->getDob());
            pat->setDiagnosis(form->getDiagnosis());
        }
    }
    this->fillListView();
}
