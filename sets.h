#ifndef SETS_H
#define SETS_H

#include <QWidget>
#include "dict.h"
#include "dict1.h"
#include "dict2.h"
#include "dict3.h"
namespace Ui {
class sets;
}

class sets : public QWidget
{
    Q_OBJECT

public:
    explicit sets(QWidget *parent = 0);
    ~sets();

signals:
    void firstWindow();  // Сигнал для первого окна на открытие

private slots:
    // Слот-обработчик нажатия кнопки
    void on_pushButton_clicked();
    void on_button2_clicked();

private:
    Ui::sets *ui;
    dict *myform;
    dict1 *myform1;
    dict2 *myform2;
    dict3 *myform3;
};

#endif // SETS_H
