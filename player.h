#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player
{
private:
    QString name;
    int musicScore;
    int filmScore;
    int gramScore;
    int sumScore;
    QString type;

public:
    Player();
    Player(QString n, int ms, int fs,int gs, QString t);
    ~Player();

    QString getName() const;
    void setName(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    int getMusicScore() const;
    void setMusicScore(int value);

    int getFilmScore() const;
    void setFilmScore(int value);

    int getGramScore() const;
    void setGramScore(int value);

    int getSumScore() const;
    void setSumScore(int value);
};

#endif // PLAYER_H
