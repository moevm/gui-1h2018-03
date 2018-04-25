#include "game.h"
#include <QtMath>
/*
 * Конструктор класса Game по умолчанию
*/
Game::Game()
{
    if (!db.isOpen())
        connectDB();

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    questCards[0] = new Music();
    questCards[1] = new Film();
    questCards[2] = new Gram();

    currentScore = 0;
    level = middle;
}

/*
 * Деструктор класса Game
*/
Game::~Game()
{
    if (db.isOpen())
        db.close();
}

/*
 * Функция возвращает объект класса Player
*/
Player Game::getPlayer() const
{
    return player;
}

/*
 * Функция изменяет текущего игрока
 * Переменные:
 * @value - новый игрок
*/
void Game::setPlayer(const Player &value)
{
    player = value;
}

void Game::setPlayerScore(int value, QString type)
{
    if(type == "music")  player.setMusicScore(value);
    if (type == "films")  player.setFilmScore(value);
    if (type == "gram")  player.setGramScore(value);


}

/* Функция производит логин пользователя.
 * Взвращает true, если пароль правильный, и
 * false, если неправильный.
 * Переменные:
 * @name - имя пользователя
 * @pass - пароль
*/
bool Game::login(QString name, QString pass)
{
    if (!db.isOpen()){
        connectDB();
    }
    QSqlQuery query = getUserFromDB(name);
    QString l;
    QString p;
    int ms = 0;
    int fs = 0;
    int gs = 0;
    QString t;

    while (query.next()) {
        l = query.value(0).toString();
        p = query.value(1).toString();
        ms = query.value(2).toInt();
        fs = query.value(3).toInt();
        t = query.value(4).toString();
        gs = query.value(5).toInt();
    }
    if (p == pass)
    {
        Player p(name, ms, fs,gs, t);
        player = p;

        return true;
    }
    else
    {
        return false;
    }
}

/*
 * Функция для разлогинивания пользователя
*/
void Game::logout()
{
    Player p;
    player = p;
}

/*
 * Функция регистрирует пользователя в игре и логинит его
 * Взвращает true, если пользователя с таким логном нет, и
 * false, если есть.
 * Параметры:
 * @name - имя пользователя
 * @pass - пароль
*/
bool Game::signup(QString name, QString pass)
{
    if (!db.isOpen()){
        connectDB();
    }
    QSqlQuery query_check = getUserFromDB(name);

    int ms = player.getMusicScore();
    int fs = player.getFilmScore();
    int gs = player.getGramScore();

    if (!query_check.next() && name != "Player"){
        QSqlQuery query;
        query.prepare("INSERT INTO players (login, password, music_score, film_score,gram_score, type)"
                      "VALUES(?, ?, ?, ?, ?,?);");
        query.addBindValue(name);
        query.addBindValue(pass);
        query.addBindValue(ms);
        query.addBindValue(fs);
        query.addBindValue(gs);
        query.addBindValue("user");
        query.exec();

        Player p(name, ms, fs,gs, "user");
        player = p;
        return true;
    }
    else {
        return false;
    }

}

/*
 * Функция проверяет залогинен ли сейчас какой-либо пользователь
*/
bool Game::isLogin()
{
    if (player.getName() != "Player"){
        return true;
    }
    else {
        return false;
    }
}
/*
 * Функция получения данных пользователя из БД.
 * Переменные:
 * @username - логин пользователя
*/
QSqlQuery Game::getUserFromDB(QString username)
{
    if (!db.isOpen())
        connectDB();
    QSqlQuery query("SELECT login, password, music_score, film_score,gram_score, type "
                    "FROM players "
                    "WHERE login IS \"" + username + "\"");
    return query;
}

/*
 * Функция получения общей статистики из БД
*/
QSqlQuery Game::getStats()
{
    if (!db.isOpen())
        connectDB();
    QSqlQuery query("SELECT login, music_score, film_score,gram_score, (music_score+film_score+gram_score) as total "
                    "FROM players "
                    "ORDER BY total DESC");
    return query;
}

/*
 * Функция для установки соединения с БД
*/
void Game::connectDB()
{
    if (!db.isOpen())
    {

     //  QSqlDatabase db;
       db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("/Users/user/Desktop/french/french/db/database.db");
        db.open();
    }
}

/*
 * Функция запуска игрового процесса
 * Переменные:
 * @type - тип игры
*/
bool Game::playGame(QString type)
{
    if (type == "music"){
        return questCards[0]->getContent();
    }
    else
      if (type == "films")
    {
        return questCards[1]->getContent();
    }
    else
          if (type == "gram")
      {
          return questCards[2]->getContent();
      }
}

/* Функция получения названия для варианта ответа
 * Переменные:
 * @type - тип игры
 * @id - номер кнопки
*/
QString Game::getAnswer(QString type, int id)
{
    if (type == "music"){
        return questCards[0]->getRandomAnsName(id-1);
    }

    else
        if (type == "films")
    {
        return questCards[1]->getRandomAnsName(id-1);
    }
    else
            if (type == "gram")
        {
            return questCards[2]->getRandomAnsName(id-1);
        }

}

/*
 * Функция получения номера для правильного варианта ответа
 * Переменные:
 * @type - тип игры
*/
QString Game::getRightAnswerId(QString type)
{
    if (type == "music"){
        return questCards[0]->getRightAnswerId();
    }
    else
        if (type == "films")
    {
        return questCards[1]->getRightAnswerId();
    }
    else
            if (type == "gram")
        {
            return questCards[2]->getRightAnswerId();
        }
}

/*
 * Функция получения названия для правильного варианта ответа
 * Переменные:
 * @type - тип игры
*/
QString Game::getRightAnswerNameStr(QString type)
{
    if (type == "music"){
        return questCards[0]->getRightAnswerName();
    }
    else
      if (type == "films")
    {
        return questCards[1]->getRightAnswerName();
    }
    else
          if (type == "gram")
      {
          return questCards[2]->getRightAnswerName();
      }
}

/*
 * Функция получения количества угаданных вопросоы
 * Переменные:
 * @type - тип игры
*/
QString Game::getRightAnswerCount(QString type)
{
    if (type == "music"){
        return questCards[0]->getUsedSize();
    }
    else
        if (type == "films")
    {
        return questCards[1]->getUsedSize();
    }
    else
            if (type == "gram"){
        return questCards[2]->getUsedSize();}
}

/*
 * Функция для проверки ответа пользователя
 * Переменные:
 * @type - тип игры
 * @id - номер кнопки ответа
*/
bool Game::checkAnswerId(QString type, int id)
{
    if (type == "music"){
        return questCards[0]->checkAnswer(id);
    }
    else
        if (type == "films")
    {
        return questCards[1]->checkAnswer(id);
    }
    else
            if (type == "gram")
        {
            return questCards[2]->checkAnswer(id);
        }
}

/*
 * Функция для перезапуска игры при выходе на главный экран
 * Переменные:
 * @type - тип игры
*/
void Game::eraseContent(QString type)
{
    if (type == "music"){
        questCards[0]->erase();
    }
    else
        if (type == "films")
    {
        questCards[1]->erase();
    }
    else
            if (type == "gram")
        {
            questCards[2]->erase();
        }
}

/*
 * Функция возвращает текущий счет в игре
*/
int Game::getCurrentScore() const
{
    return currentScore;
}

/*
 * Функция изменяет текущий счет в игре
 * Параметры:
 * @value - новое значение текущего счета
 */
void Game::setCurrentScore(int value)
{
    currentScore = value;
}

/*
 * Функция вычисляет количество баллов, начисляемых игроку за верный ответ
 * Параметры:
 * @sec - количество секунд, прошедших со старта текущей карточки +1
 * @type - тип игры
 */
int Game::calculateScore(int sec, QString type)
{
    return ((type == "music") ? 100 : 75) / sqrt(sec) * level;
}

void Game::changeScoreInDB(QString type, int score)
{
    if (!db.isOpen()){
        connectDB();
    }

    if (type == "music"){
        QSqlQuery query("UPDATE players"
                        " SET music_score = '" + QString::number(score) +
                        "' WHERE login = '" + player.getName()+"'");
    }
    else
        if (type == "films")
    {
        QSqlQuery query("UPDATE players"
                        " SET film_score = '" + QString::number(score) +
                        "' WHERE login = '" + player.getName()+"'");
    }
    else
            if (type == "gram")
        {
            QSqlQuery query("UPDATE players"
                            " SET gram_score = '" + QString::number(score) +
                            "' WHERE login = '" + player.getName()+"'");
        }

}
