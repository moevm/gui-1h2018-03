#ifndef GRAM_H
#define GRAM_H
#include "questcards.h"

class Gram : public QuestCards
{
public:
    Gram();
    bool play();
    bool getContent();
    QString getRandomAnsName(int id);
    bool checkUsedSize();
};
#endif // GRAM_H
