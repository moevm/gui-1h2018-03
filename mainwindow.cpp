#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sets.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sWindow = new sets();


    // подключаем к слоту запуска главного окна по кнопке во втором окне
      connect(sWindow, &sets::firstWindow, this, &MainWindow::show);


      QPixmap bkgnd(":/res/pic.jpg");
     bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
      QPalette palette;
      palette.setBrush(QPalette::Background, bkgnd);
      this->setPalette(palette);
    //  QPixmap myPixmap( ":/res/logo.png" );
      //myPixmap = myPixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
     // ui->label->setPixmap( myPixmap );

}

MainWindow::~MainWindow()
{


    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    sWindow->show();  // Показываем второе окно
        //this->close();
}

void MainWindow::on_pushButton_4_clicked()
{
    close();
}
