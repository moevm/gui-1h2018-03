#include "questcards.h"

QuestCards::QuestCards()
{
}

QuestCards::~QuestCards()
{

}

QString QuestCards::getRightAnswerId()
{
    return QString::number(answerId);
}

QString QuestCards::getRightAnswerName()
{
    QSqlQuery query("SELECT id, name FROM " + type + " WHERE id IS \"" + QString::number(answerId) + "\"");
    QString id_str;
    QString name_str;
    while (query.next())
        {
        id_str = query.value(0).toString();
        name_str = query.value(1).toString();
        }

    return name_str;
}

QString QuestCards::getUsedSize()
{
    return QString::number(usedContent.size()-1);
}

int QuestCards::getNum()
{
    int randomId = qrand() % N +1;
    QListIterator <int> id(usedContent);
    while(id.hasNext()){
        if(randomId == id.next()){
            return randomId = getNum();
        }
    }
    return randomId;
}

void QuestCards::getRandomAns()
{
    if (N > 3){
        bool check = true;
        randomId.clear();
        for (int i = 0; i < 3; i++){
            int id = qrand() % N +1;
            QListIterator <int> id_iter(randomId);
            if (id == answerId){
                i--;
                continue;
            }
            else
                while(id_iter.hasNext()){
                    if(id == id_iter.next()){
                        i--;
                        check = false;
                        break;
                    }
                }
            if(check)
                randomId.append(id);
            else
                check = true;
        }
    }
}

void QuestCards::erase()
{
    usedContent.clear();
    randomId.clear();
    answerId = 0;
    N = 0;
}


bool QuestCards::checkAnswer(int id)
{
    if (randomId.at(id) == answerId)
        return true;
    else
        return false;
}
