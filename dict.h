#ifndef DICT_H
#define DICT_H

#include <QWidget>

namespace Ui {
class dict;
}

class dict : public QWidget
{
    Q_OBJECT

public:
    explicit dict(QWidget *parent = 0);
    ~dict();

private:
    Ui::dict *ui;
};

#endif // DICT_H
