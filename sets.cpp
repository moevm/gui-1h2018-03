#include "sets.h"
#include "ui_sets.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
sets::sets(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sets)
{
    ui->setupUi(this);
    //Подключаем базу данных
   QSqlDatabase db;
   db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("/Users/user/words.db");
   db.open();

   //Осуществляем запрос
   QSqlQuery query;
   query.exec("SELECT id, french, russian FROM words ");

   //Выводим значения из запроса
   while (query.next())
   {
   QString _id = query.value(0).toString();
   QString french = query.value(1).toString();
   QString russian = query.value(2).toString();
   ui->textEdit->insertPlainText(_id+" "+french+" "+russian+"\n");
   ui ->textEdit->insertPlainText("hello");
   }
}

sets::~sets()
{
    delete ui;
}

void sets::on_pushButton_clicked()
{
    this->close();      // Закрываем окно
    emit firstWindow(); // И вызываем сигнал на открытие главного окн


}
