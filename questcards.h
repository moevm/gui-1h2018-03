#ifndef QUESTCARDS_H
#define QUESTCARDS_H

#include <QString>
#include <QSqlQuery>
#include "QTime"
#include <QList>

class QuestCards
{
protected:
    QList <int> usedContent;
    QList <int> randomId;
    int answerId;
    int N;
    QString type;

public:
    QuestCards();
    virtual QString getRandomAnsName(int id) = 0;
    virtual ~QuestCards() = 0;
    virtual bool getContent() = 0;
    virtual bool checkUsedSize() = 0;

    int getNum();
    QString getRightAnswerId();
    QString getRightAnswerName();
    QString getUsedSize();
    void getRandomAns();

    bool checkAnswer(int id);
    void erase();
};

#endif // QUESTCARDS_H
