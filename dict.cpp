#include "dict.h"
#include "ui_dict.h"
#include "QSqlDatabase"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QDebug>

dict::dict(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dict)
{
    ui->setupUi(this);
 /*  QSqlDatabase db1;
  db1 = QSqlDatabase::addDatabase("QSQLITE");
   db1.setDatabaseName("/Users/user/eda.db");
   db1.open();

    //Осуществляем запрос
    QSqlQuery query1;
    query1.exec("SELECT id, french, trans, rus FROM eda ");


    //Выводим значения из запроса
    while (query1.next())
    {
    QString id = query1.value(0).toString();
    qDebug() << id;
    QString french = query1.value(1).toString();
    QString trans = query1.value(2).toString();
    QString rus = query1.value(3).toString();
    ui->textBrowser1->insertPlainText(french+"\n");
    ui->textBrowser2->insertPlainText(trans+"\n");
    ui->textBrowser3->insertPlainText(rus+"\n");


    }
    */
    QPixmap bkgnd(":/images/res/background.jpg");
   bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

dict::~dict()
{
    delete ui;
}
