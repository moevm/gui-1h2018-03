#include "dict3.h"
#include "ui_dict3.h"

dict3::dict3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dict3)
{
    ui->setupUi(this);
}

dict3::~dict3()
{
    delete ui;
}
