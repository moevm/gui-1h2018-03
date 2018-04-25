#ifndef MUSIC_H
#define MUSIC_H

#include "questcards.h"

class Music : public QuestCards
{
public:
    Music();
    bool play();
    bool getContent();
    QString getRandomAnsName(int id);
    bool checkUsedSize();
};

#endif // MUSIC_H
