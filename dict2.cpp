#include "dict2.h"
#include "ui_dict2.h"

dict2::dict2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dict2)
{
    ui->setupUi(this);
}

dict2::~dict2()
{
    delete ui;
}
