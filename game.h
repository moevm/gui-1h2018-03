#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "music.h"
#include "film.h"
#include <QString>
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include "QApplication"

enum levelType {easy = 1, middle, difficult};

class Game
{
private:
    Player player;
    QuestCards *questCards[2];
    QSqlDatabase db;
    int currentScore;
    levelType level;

public:
    Game();
    ~Game();

    Player getPlayer() const;
    void setPlayer(const Player &value);
    void setPlayerScore(int value, QString type);


    bool login(QString name, QString pass);
    void logout();
    bool isLogin();
    bool signup(QString name, QString pass);
    QSqlQuery getUserFromDB(QString username);
    QSqlQuery getStats();

    void connectDB();

    bool playGame(QString type);

    QString getAnswer(QString type, int id);
    QString getRightAnswerId(QString type);
    QString getRightAnswerNameStr(QString type);
    QString getRightAnswerCount(QString type);
    bool checkAnswerId(QString type, int id);
    void eraseContent(QString type);
    int getCurrentScore() const;
    void setCurrentScore(int value);
    int calculateScore(int sec, QString type);
    void changeScoreInDB(QString type, int score);
};

#endif // GAME_H
