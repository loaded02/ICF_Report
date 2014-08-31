#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QWidget>

namespace Ui {
class Functions;
}

class Functions : public QWidget
{
    Q_OBJECT

public:
    explicit Functions(QWidget *parent = 0);
    ~Functions();

private:
    Ui::Functions *ui;
};

#endif // FUNCTIONS_H
