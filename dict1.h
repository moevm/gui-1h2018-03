#ifndef DICT1_H
#define DICT1_H

#include <QWidget>

namespace Ui {
class dict1;
}

class dict1 : public QWidget
{
    Q_OBJECT

public:
    explicit dict1(QWidget *parent = 0);
    ~dict1();

private:
    Ui::dict1 *ui;
};

#endif // DICT1_H
