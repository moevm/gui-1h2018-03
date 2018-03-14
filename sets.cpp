#include "sets.h"
#include "ui_sets.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include "dict.h"
sets::sets(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sets)
{
    ui->setupUi(this);
    myform = new dict();
    connect(ui->button1, SIGNAL(clicked()), myform, SLOT(show()));


    // подключаем к слоту запуска главного окна по кнопке во втором окне
    //  connect(dWindow, &dict::setsWindow, this, &sWindow::show);
    QPixmap bkgnd(":/res/fon1.jpg");
   bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    //Подключаем базу данных

   ui->button1->setFixedSize(100,100);
   ui->button1->setFlat(true);
   ui->button1->setIconSize(QSize(100, 100));

   ui->buttton2->setFixedSize(100,100);
   ui->buttton2->setFlat(true);
   ui->buttton2->setIconSize(QSize(100, 100));

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


