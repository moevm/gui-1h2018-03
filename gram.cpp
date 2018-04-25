#include "gram.h"

Gram::Gram():QuestCards()
{
    type = "gram";
}

bool Gram::getContent()
{
    if (checkUsedSize()){
        answerId = getNum();
        usedContent.append(answerId);
        getRandomAns();
        randomId.insert(qrand()%4, answerId);
        return true;
    }
    else
        return false;
}

QString Gram::getRandomAnsName(int id)
{
    QSqlQuery query("SELECT id, name FROM " + type + " WHERE id IS \"" + QString::number(randomId.at(id)) + "\"");
    QString id_str;
    QString name_str;
    while (query.next())
        {
        id_str = query.value(0).toString();
        name_str = query.value(1).toString();
        }

    return name_str;
}

bool Gram::checkUsedSize()
{
    QSqlQuery query("SELECT id FROM " + type);
    query.last();
    N = query.at() + 1;
    if (N == usedContent.size())
        return false;
    return true;
}

