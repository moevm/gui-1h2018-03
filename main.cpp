#include "mainwindow.h"
#include <QApplication>
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("QMainWindow {background: 'yellow';}");
    w.setStyleSheet("background-image: /Users/user/Desktop/GUI/GUI/2.jpg");
    w.show();

    return a.exec();
}
