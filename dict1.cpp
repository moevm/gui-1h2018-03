#include "dict1.h"
#include "ui_dict1.h"

dict1::dict1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dict1)
{
    ui->setupUi(this);
}

dict1::~dict1()
{
    delete ui;
}
