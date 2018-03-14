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
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/user/eda.db");
    db.open();

    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT id, french, trans, rus FROM eda ");


    //Выводим значения из запроса
    while (query.next())
    {
    QString id = query.value(0).toString();
    qDebug() << id;
    QString french = query.value(1).toString();
    QString trans = query.value(2).toString();
    QString rus = query.value(3).toString();
    ui->textBrowser1->insertPlainText(french+"\n");
    ui->textBrowser2->insertPlainText(trans+"\n");
    ui->textBrowser3->insertPlainText(rus+"\n");

    }
    QPixmap bkgnd(":/res/fon1.jpg");
   bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

dict::~dict()
{
    delete ui;
}
