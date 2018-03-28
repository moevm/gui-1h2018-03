#ifndef DICT3_H
#define DICT3_H

#include <QWidget>

namespace Ui {
class dict3;
}

class dict3 : public QWidget
{
    Q_OBJECT

public:
    explicit dict3(QWidget *parent = 0);
    ~dict3();

private:
    Ui::dict3 *ui;
};

#endif // DICT3_H
