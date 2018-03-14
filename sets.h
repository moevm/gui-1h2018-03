#ifndef SETS_H
#define SETS_H

#include <QWidget>
#include "dict.h"
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
private:
    Ui::sets *ui;
    dict *myform;
};

#endif // SETS_H
