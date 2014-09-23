#include "gui_showperson.h"
#include "ui_gui_showperson.h"

void GUI_ShowPerson::fillListView()
{
    ui->listWidget->clear();
    if (art == 'p') {
        for (int i=0; i<icfcontroller->sizeOfPatients(); i++) {
            Patient* actPerson = icfcontroller->getPatient(i);
            new QListWidgetItem(QString::number(actPerson->getId()) + " " + actPerson->getName() + " " + actPerson->getSurname(),ui->listWidget);
        }
    } else if (art == 't') {
        for (int i=0; i<icfcontroller->sizeOfTherapists(); i++) {
            Therapist* actPerson = icfcontroller->getTherapist(i);
            new QListWidgetItem(QString::number(actPerson->getId()) + " " + actPerson->getName() + " " + actPerson->getSurname(),ui->listWidget);
        }
    } else {
        std::cerr << "Art ist weder p noch t" << std::endl;
    }
}

GUI_ShowPerson::GUI_ShowPerson(ICFController *controller, char art, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUI_ShowPerson),icfcontroller(controller),art(art){
    ui->setupUi(this);
    this->fillListView();
    if (art == 'p') {
        connect(ui->newButton,SIGNAL(clicked()),static_cast<MainWindow*>(parent),SLOT(on_actionNew_Patient_triggered()));
    } else if (art == 't') {
        connect(ui->newButton,SIGNAL(clicked()),static_cast<MainWindow*>(parent),SLOT(on_actionNew_Therapist_triggered()));
    } else {
        std::cerr << "Art ist weder p noch t" << std::endl;
    }
}

GUI_ShowPerson::~GUI_ShowPerson()
{
    delete ui;
}

void GUI_ShowPerson::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QStringList stringList = item->text().split(" ");
    GUI_NewPerson* form = new GUI_NewPerson(this);
    if (art == 't') {
        if (Therapist* ther = icfcontroller->findTherapist(stringList[0].toInt())) {
            form->therapistAppearance();
            form->setWindowTitle("Edit Therapist");
            form->setSurname(ther->getSurname());
            form->setName(ther->getName());
            if (form->exec()) {
                ther->setSurname(form->getSurname());
                ther->setName(form->getName());
            }
        }
    }
    else if (art == 'p') {
        if (Patient* pat = icfcontroller->findPatient(stringList[0].toInt())) {
            form->setSurname(pat->getSurname());
            form->setName(pat->getName());
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
    } else {
        std::cerr << "Art ist weder p noch t" << std::endl;
    }
    this->fillListView();
}

void GUI_ShowPerson::on_closeButton_clicked()
{
    this->close();
}

void GUI_ShowPerson::on_editButton_clicked()
{
    QListWidgetItem* item = ui->listWidget->currentItem();
    if (item)
        this->on_listWidget_itemDoubleClicked(item);
}

void GUI_ShowPerson::on_removeButton_clicked()
{
    QListWidgetItem* item = ui->listWidget->currentItem();
    if (item) {
        QStringList stringList = item->text().split(" ");
        switch (art) {
        case 't':
            icfcontroller->removeTherapist(stringList[0].toInt());
            break;
        case 'p':
            icfcontroller->removePatient(stringList[0].toInt());
            break;
        default:std::cerr << "Art ist weder Pat noch Ther" << std::endl;
            break;
        }
        this->fillListView();
    }
}

void GUI_ShowPerson::on_refreshButton_clicked()
{
    this->fillListView();
}
