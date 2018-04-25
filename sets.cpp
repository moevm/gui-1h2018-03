#include "sets.h"
#include "ui_sets.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include "dict.h"
#include "dict1.h"
#include "dict2.h"
#include "dict3.h"
sets::sets(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sets)
{
    ui->setupUi(this);
    myform = new dict();
    myform1 = new dict1();
    myform2 = new dict2();
    myform3 = new dict3();
    connect(ui->button1, SIGNAL(clicked()), myform, SLOT(show()));
    connect(ui->button2, SIGNAL(clicked()), myform1, SLOT(show()));
    connect(ui->button3, SIGNAL(clicked()), myform2, SLOT(show()));
    connect(ui->button4, SIGNAL(clicked()), myform3, SLOT(show()));
    myform = new dict();
    connect(ui->button1, SIGNAL(clicked()), myform, SLOT(show()));


   // подключаем к слоту запуска главного окна по кнопке во втором окне
      //connect(dWindow, &dict::setsWindow, this, &sWindow::show);
   QPixmap bkgnd(":/images/res/background.jpg");
  bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
  QPalette palette;
  palette.setBrush(QPalette::Background, bkgnd);
   this->setPalette(palette);
    //Подключаем базу данных

   ui->button1->setFixedSize(100,100);
   ui->button1->setFlat(true);
   ui->button1->setIconSize(QSize(100, 100));

   ui->button2->setFixedSize(100,100);
   ui->button2->setFlat(true);
   ui->button2->setIconSize(QSize(100, 100));

   ui->button3->setFixedSize(100,100);
   ui->button3->setFlat(true);
   ui->button3->setIconSize(QSize(100, 100));

   ui->button4->setFixedSize(100,100);
   ui->button4->setFlat(true);
   ui->button4->setIconSize(QSize(100, 100));

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



void sets::on_button2_clicked()
{
    this->close();
}
