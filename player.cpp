#include "player.h"

Player::Player()
{
    name = "Player";
    musicScore = 0;
    filmScore = 0;
    gramScore = 0;
    type = "User";
    sumScore = musicScore + filmScore + gramScore;
}

Player::Player(QString n, int ms, int fs,int gs, QString t)
{
    name = n;
    musicScore = ms;
    filmScore = fs;
    gramScore = gs;
    type = t;
    sumScore = musicScore + filmScore + gramScore ;
}
Player::~Player()
{

}

QString Player::getName() const
{
    return name;
}

void Player::setName(const QString &value)
{
    name = value;
}

QString Player::getType() const
{
    return type;
}

void Player::setType(const QString &value)
{
    type = value;
}

int Player::getMusicScore() const
{
    return musicScore;
}

void Player::setMusicScore(int value)
{
    musicScore = value;

    sumScore = filmScore + musicScore + gramScore;
}
int Player::getFilmScore() const
{
    return filmScore;
}

void Player::setFilmScore(int value)
{
    filmScore = value;

    sumScore = filmScore + musicScore + gramScore;
}

int Player::getGramScore() const
{
    return gramScore;
}

void Player::setGramScore(int value)
{
    gramScore = value;

    sumScore = filmScore + musicScore + gramScore;
}
int Player::getSumScore() const
{
    return sumScore;
}

void Player::setSumScore(int value)
{
    sumScore = value;
}

