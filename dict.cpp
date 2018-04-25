#include "dict.h"
#include "ui_dict.h"
#include "QSqlDatabase"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QDebug>
#include "game.h"

dict::dict(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dict)
{
    ui->setupUi(this);
   /* QSqlQuery query("SELECT id, name FROM " + type + " WHERE id IS \"" + QString::number(randomId.at(id)) + "\"");
    QString id_str;
    QString name_str;
    while (query.next())
        {
        id_str = query.value(0).toString();
        name_str = query.value(1).toString();
        }

    return name_str;
    */
    //onnectDB();
    QSqlQuery query;
    query.exec("SELECT id, fr, trans, rus FROM words_animals ");


    //Выводим значения из запроса
    while (query.next())
    {
    QString id = query.value(0).toString();
    qDebug() << id;
    QString fr = query.value(1).toString();
    QString trans = query.value(2).toString();
    QString rus = query.value(3).toString();
    ui->textBrowser1->insertPlainText(fr+"\n");
    ui->textBrowser2->insertPlainText(trans+"\n");
    ui->textBrowser3->insertPlainText(rus+"\n");


    }
}

dict::~dict()
{
    delete ui;
}
