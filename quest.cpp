#include "quest.h"
#include "ui_quest.h"

quest::quest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::quest)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/res/fon1.jpg");
   bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    ui->yes->setFixedSize(90,90);
   ui->yes->setFlat(true);
    ui->yes->setIconSize(QSize(90, 90));

    ui->no->setFixedSize(90,90);
   ui->no->setFlat(true);
    ui->no->setIconSize(QSize(90, 90));

    this->setWindowTitle(QString::fromLocal8Bit("Уследи за цветом"));

    sum=0;
    cur=0;

    left = this->findChild<QLabel *>("left");
    right = this->findChild<QLabel *>("right");
    res = this->findChild<QLabel *>("res");





}

void quest::init(int colors, int games,int comp)
{

    this->colors=colors;
    this->games=games;
    this->comp=comp;
    game();
}

void quest::game()
{
    s1=qrand() % colors;
    c1=qrand() % colors;
    s2=qrand() % colors;
    c2=qrand() % colors;

    int p=qrand()%100;
    if(p<45) s1=c2;

    labelColor(left,c1);
    labelText(left,s1);

    labelColor(right,c2);
    labelText(right,s2);
}

void quest::labelColor(QLabel *l, int x)
{
    switch(x)
    {
      case 0:
        l->setStyleSheet("color: rgb(255, 0, 0)");
        break;

      case 1:
        l->setStyleSheet("color: rgb(0, 255, 0)");
        break;

      case 2:
        l->setStyleSheet("color: rgb(0, 0, 255)");
        break;

      case 3:
        l->setStyleSheet("color: rgb(0, 0, 0)");
      break;

      case 4:
        l->setStyleSheet("color: rgb(230, 215, 5)");
      break;
    }
}

void quest::labelText(QLabel *l, int x)
{
    switch(x)
    {
      case 0:
        l->setText(QString::fromLocal8Bit("Красный"));
        break;

      case 1:
        l->setText(QString::fromLocal8Bit("Зеленый"));
        break;

      case 2:
        l->setText(QString::fromLocal8Bit("Синий"));
        break;

      case 3:
        l->setText(QString::fromLocal8Bit("Черный"));
      break;

      case 4:
        l->setText(QString::fromLocal8Bit("Желтый"));
      break;
    }
}

void quest::yes()
{
    if(s1==c2)
    {
        sum++;
        QString s=QString::number(sum);
        res->setText(s);
    }
    cur++;
    if(cur>=games)
    {

        labelColor(left,3);
        labelColor(right,3);
        left->setText(QString::fromLocal8Bit("Ваш реузльтат:"));
        double b=(double) (100*sum)/games;



        QString r=QString::number((int)b)+"%";
        right->setText(r);
       // yesb->setEnabled(false);
      //  yesb->setVisible(false);
     //   nob->setEnabled(false);
     //   nob->setVisible(false);
    }
    else game();
}

void quest::no()
{
    if(s1!=c2)
    {
        sum++;
        QString s=QString::number(sum);
        res->setText(s);
    }
    cur++;
    if(cur>=games)
    {
        labelColor(left,3);
        labelColor(right,3);
        left->setText(QString::fromLocal8Bit("Ваш реузльтат:"));
        double b=(double) (100*sum)/games;

        //this->sqlhelp->addStats(QString::fromLocal8Bit("Уследи за цветом"),comp,b);

        QString r=QString::number(b)+"%";
        right->setText(r);
      //  yesb->setEnabled(false);
     //   yesb->setVisible(false);
     //   nob->setEnabled(false);
     //   nob->setVisible(false);
    }
    else game();
}



quest::~quest()
{
    delete ui;
}
