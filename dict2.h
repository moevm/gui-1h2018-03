#ifndef DICT2_H
#define DICT2_H

#include <QWidget>

namespace Ui {
class dict2;
}

class dict2 : public QWidget
{
    Q_OBJECT

public:
    explicit dict2(QWidget *parent = 0);
    ~dict2();

private:
    Ui::dict2 *ui;
};

#endif // DICT2_H
