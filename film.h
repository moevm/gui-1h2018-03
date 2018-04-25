#ifndef FILM_H
#define FILM_H

#include "questcards.h"

class Film : public QuestCards
{
public:
    Film();
    bool getContent();
    QString getRandomAnsName(int id);
    bool checkUsedSize();
};

#endif // FILM_H
