#ifndef QUEST_H
#define QUEST_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>


namespace Ui {
class quest;
}

class quest : public QWidget
{
    Q_OBJECT

public:
    explicit quest(QWidget *parent = 0);
    void game();
    void init(int colors,int games,int comp);
    ~quest();

public slots:
    void yes();
    void no();

private:
    Ui::quest *ui;
    QLabel *left;
    QLabel *right;
    QLabel *res;
    QPushButton *yesb;
    QPushButton *nob;
    int comp;
    int s1;
    int c1;
    int s2;
    int c2;
    int sum; // ������� ���������
    int colors; // ���������� ������������ ������
    int games; // �������� ���������� �������
    int cur; // ������� ����� �������

    void labelColor(QLabel *l,int x);
    void labelText(QLabel *l,int x);
};

#endif // QUEST_H
