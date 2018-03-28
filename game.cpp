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
    type == "music" ? player.setMusicScore(value) : player.setFilmScore(value);
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
    QString t;

    while (query.next()) {
        l = query.value(0).toString();
        p = query.value(1).toString();
        ms = query.value(2).toInt();
        fs = query.value(3).toInt();
        t = query.value(4).toString();
    }
    if (p == pass)
    {
        Player p(name, ms, fs, t);
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

    if (!query_check.next() && name != "Player"){
        QSqlQuery query;
        query.prepare("INSERT INTO players (login, password, music_score, film_score, type)"
                      "VALUES(?, ?, ?, ?, ?);");
        query.addBindValue(name);
        query.addBindValue(pass);
        query.addBindValue(ms);
        query.addBindValue(fs);
        query.addBindValue("user");
        query.exec();

        Player p(name, ms, fs, "user");
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
    QSqlQuery query("SELECT login, password, music_score, film_score, type "
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
    QSqlQuery query("SELECT login, music_score, film_score, (music_score+film_score) as total "
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
        db.setDatabaseName("/Users/user/Downloads/gui-1h2017-14-master-2/db/database.db");
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
    {
        return questCards[1]->getContent();
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
    {
        return questCards[1]->getRandomAnsName(id-1);
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
    {
        return questCards[1]->getRightAnswerId();
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
    {
        return questCards[1]->getRightAnswerName();
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
    {
        return questCards[1]->getUsedSize();
    }
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
    {
        return questCards[1]->checkAnswer(id);
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
    {
        questCards[1]->erase();
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
    {
        QSqlQuery query("UPDATE players"
                        " SET film_score = '" + QString::number(score) +
                        "' WHERE login = '" + player.getName()+"'");
    }
}
