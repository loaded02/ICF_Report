#ifndef GUI_PRINTWINDOW_H
#define GUI_PRINTWINDOW_H

#include <QDialog>
#include "icfcontroller.h"

namespace Ui {
class GUI_PrintWindow;
}

class GUI_PrintWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GUI_PrintWindow(ICFController* icfController, QWidget *parent = 0);
    ~GUI_PrintWindow();

public slots:
    virtual void accept();
    void onProcessFinished(int status);
private:
    Ui::GUI_PrintWindow *ui;
    ICFController *icfController;
};

#endif // GUI_PRINTWINDOW_H
