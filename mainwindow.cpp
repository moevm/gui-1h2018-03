#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sets.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sWindow = new sets();
    connect(sWindow, &sets::firstWindow, this, &MainWindow::show);
    bkgdMusicValue = 20;
    musicPlayerValue = 80;
    sizeBtn = 170;
    actualBtn = "music";
    lenBtn = 320;
    checkInGame = false;

    ui->bkgdMusicVolumeSlider->setValue(bkgdMusicValue);
    ui->musicPlayerVolumeSlider->setValue(musicPlayerValue);

    QPixmap bkgnd(":/images/res/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(15);
    shadowEffect->setOffset(3);
    ui->centralWidget->setGraphicsEffect(shadowEffect);

    setNameAndScore();

    ui->gameWidget->setCurrentWidget(ui->pageMain);
    ui->menuWidget->setCurrentWidget(ui->pageMenu);

    hideUserInfo();
    hideScoreInfo();
    showSpecialButtons();
    showLoginButtons();

    mediaPlayer = new QMediaPlayer;
    mediaPlaylist = new QMediaPlaylist(mediaPlayer);
    backgroundMusic();

    tmr = new QTimer(this);
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTimer()));

    tmr_btn = new QTimer(this);
    tmr_btn->setInterval(5000);
    connect(tmr_btn, SIGNAL(timeout()), this, SLOT(updateButton()));

    tmr_end = new QTimer(this);
    tmr_end->setInterval(5000);
    connect(tmr_end, SIGNAL(timeout()), this, SLOT(gameEnd()));    

    tmr_mainUp = new QTimer(this);
    tmr_mainUp->setInterval(3000);
    connect(tmr_mainUp, SIGNAL(timeout()), this, SLOT(resizeBtnUp()));

    tmr_mainDown = new QTimer(this);
    tmr_mainDown->setInterval(50);
    connect(tmr_mainDown, SIGNAL(timeout()), this, SLOT(resizeBtnDown()));

    maxSeconds = MAX_SECONDS_MIDDLE;
    seconds = maxSeconds;
    tmr_mainUp->start();


}

MainWindow::~MainWindow()
{
    delete ui;
    delete tmr;
}

void MainWindow::hideUserInfo()
{
    ui->name->hide();
    ui->score->hide();
    ui->verticalSpacer_16->changeSize(20, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void MainWindow::showUserInfo()
{
    ui->name->show();
    ui->score->show();
    ui->verticalSpacer_16->changeSize(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void MainWindow::hideScoreInfo()
{
    ui->answerLabel->hide();
    ui->countRightAnswers->hide();
    ui->timeLabel->hide();
    ui->secondsLabel->hide();
    ui->verticalSpacer_2->changeSize(20, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void MainWindow::showScoreInfo()
{
    ui->answerLabel->show();
    ui->countRightAnswers->show();
    ui->timeLabel->show();
    ui->secondsLabel->show();
    ui->verticalSpacer_2->changeSize(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void MainWindow::hideSpecialButtons()
{

    ui->exitButton->hide();
    ui->mainpageButton->show();
}

void MainWindow::showSpecialButtons()
{

    ui->exitButton->show();
    ui->mainpageButton->hide();
}

void MainWindow::hideLoginButtons()
{

    ui->signupButton_2->hide();
}

void MainWindow::showLoginButtons()
{
    ui->signupButton_2->show();
}

void MainWindow::installEventFilterOnBtns()
{
    ui->answerButton_1->installEventFilter(this);
    ui->answerButton_2->installEventFilter(this);
    ui->answerButton_3->installEventFilter(this);
    ui->answerButton_4->installEventFilter(this);
    ui->answerButton_5->installEventFilter(this);
    ui->answerButton_6->installEventFilter(this);
    ui->answerButton_7->installEventFilter(this);
    ui->answerButton_8->installEventFilter(this);
    ui->answerButton_9->installEventFilter(this);
    ui->answerButton_10->installEventFilter(this);
    ui->answerButton_11->installEventFilter(this);
    ui->answerButton_12->installEventFilter(this);
    ui->pageMusic->installEventFilter(this);
    ui->pageFilm->installEventFilter(this);
    ui->pageGram->installEventFilter(this);
}

void MainWindow::removeEventFilterOnBtns()
{
    ui->answerButton_1->removeEventFilter(this);
    ui->answerButton_2->removeEventFilter(this);
    ui->answerButton_3->removeEventFilter(this);
    ui->answerButton_4->removeEventFilter(this);
    ui->answerButton_5->removeEventFilter(this);
    ui->answerButton_6->removeEventFilter(this);
    ui->answerButton_7->removeEventFilter(this);
    ui->answerButton_8->removeEventFilter(this);
    ui->answerButton_9->removeEventFilter(this);
    ui->answerButton_10->removeEventFilter(this);
    ui->answerButton_11->removeEventFilter(this);
    ui->answerButton_12->removeEventFilter(this);
    ui->pageMusic->removeEventFilter(this);
    ui->pageFilm->removeEventFilter(this);
    ui->pageGram->removeEventFilter(this);
}

void MainWindow::on_playMusic_clicked()
{
    actualGame = "music";
    checkInGame = true;

    changeCurrentScore(0);

    ui->gameWidget->setCurrentWidget(ui->pageMusic);
    showUserInfo();
    showScoreInfo();
    hideLoginButtons();
    hideSpecialButtons();

    tmr->start();

    game.eraseContent(actualGame);

    updatePlayScreen();

    installEventFilterOnBtns();
}

void MainWindow::on_playFilm_clicked()
{
    actualGame = "films";
    checkInGame = true;

    changeCurrentScore(0);

    ui->gameWidget->setCurrentWidget(ui->pageFilm);
    showUserInfo();
    showScoreInfo();
    hideLoginButtons();
    hideSpecialButtons();

    tmr->start();

    game.eraseContent(actualGame);

    updatePlayScreen();

    installEventFilterOnBtns();
}
void MainWindow::on_playGram_clicked()
{
    actualGame = "gram";
    checkInGame = true;

    changeCurrentScore(0);

    ui->gameWidget->setCurrentWidget(ui->pageGram);
    showUserInfo();
    showScoreInfo();
    hideLoginButtons();
    hideSpecialButtons();

    tmr->start();

    game.eraseContent(actualGame);

    updatePlayScreen();

    installEventFilterOnBtns();
}

void MainWindow::on_mainpageButton_clicked()
{
    bool check = true;
    if (checkInGame)
    {
        check = QMessageBox::warning(0,
                                     "Внимание!",
                                     "Вы потеряете игровой процесс."
                                     "\nВыйти на главный экран?",
                                     "Нет",
                                     "Да",
                                     QString(),
                                     0,
                                     1
                                    );

    }
    if (check)
    {
        tmr->stop();
        tmr_btn->stop();
        tmr_end->stop();
        if (checkInGame){
            checkInGame = false;
            backgroundMusic();
            removeEventFilterOnBtns();
        }
        ui->score->setText("<html><head/><body><p align=\"center\">"
                           "<span style=\" font-size:18pt; color:#ffffff;\">" +
                           QString::number(game.getPlayer().getSumScore()) +
                           "</span></p></body></html>");
        ui->gameWidget->setCurrentWidget(ui->pageMain);
        if (game.isLogin()){
            showUserInfo();
            hideLoginButtons();
        }
        else {
            hideUserInfo();
            showLoginButtons();
        }

        hideScoreInfo();
        showSpecialButtons();
    }
}

void MainWindow::on_statButton_clicked()
{
    bool check = true;
    if (checkInGame)
    {
        check = QMessageBox::warning(0,
                                     "Внимание!",
                                     "Вы потеряете игровой процесс."
                                     "\nОткрыть статистику?",
                                     "Нет",
                                     "Да",
                                     QString(),
                                     0,
                                     1
                                    );

    }
    if (check)
    {
        tmr->stop();
        tmr_btn->stop();
        tmr_end->stop();
        if (checkInGame){
            checkInGame = false;
            backgroundMusic();
            hideScoreInfo();
            removeEventFilterOnBtns();
        }
        ui->score->setText("<html><head/><body><p align=\"center\">"
                           "<span style=\" font-size:18pt; color:#ffffff;\">" +
                           QString::number(game.getPlayer().getSumScore()) +
                           "</span></p></body></html>");
        ui->gameWidget->setCurrentWidget(ui->pageStats);
        showUserInfo();
        hideLoginButtons();

        hideSpecialButtons();
        ui->tryagainButton->hide();

        statsOut();
    }
}


void MainWindow::on_cancelButton_clicked()
{
    on_mainpageButton_clicked();
}

void MainWindow::on_exitButton_clicked()
{
    close();
}


void MainWindow::on_signupButton_clicked()
{
    if (ui->username_2->text() != "" && ui->password_2->text() != "")
    {
        if(game.signup(ui->username_2->text(), ui->password_2->text()))
        {

            setNameAndScore();
            on_mainpageButton_clicked();
        }
        else
        {
            ui->label_6->setText("<html><head/><body><p align=\"center\"><span style=\" color:#ffffff;\">"
                                 "Игрок с таким логином</span></p><p align=\"center\"><span style=\" color:#ffffff;\">"
                                 "уже зарегистрирован!</span></p></body></html>");
        }
    }
    else
    {
        ui->label_6->setText("<html><head/><body><p align=\"center\"><span style=\" color:#ffffff;\">"
                             "Все поля должны быть заполнены!</span></p></body></html>");
    }
}


void MainWindow::on_signupButton_2_clicked()
{
     ui->gameWidget->setCurrentWidget(ui->pageSignup);
     showUserInfo();
     hideLoginButtons();

     hideSpecialButtons();
}

void MainWindow::on_answerButton_1_clicked()
{
    checkAnswer(1);
}

void MainWindow::on_answerButton_2_clicked()
{
    checkAnswer(2);
}

void MainWindow::on_answerButton_3_clicked()
{
    checkAnswer(3);
}

void MainWindow::on_answerButton_4_clicked()
{
    checkAnswer(4);
}

void MainWindow::on_answerButton_5_clicked()
{
    checkAnswer(1);
}

void MainWindow::on_answerButton_6_clicked()
{
    checkAnswer(2);
}

void MainWindow::on_answerButton_7_clicked()
{
    checkAnswer(3);
}

void MainWindow::on_answerButton_8_clicked()
{
    checkAnswer(4);
}

void MainWindow::on_answerButton_9_clicked()
{
    checkAnswer(1);
}

void MainWindow::on_answerButton_10_clicked()
{
    checkAnswer(2);

}

void MainWindow::on_answerButton_11_clicked()
{
    checkAnswer(3);
}

void MainWindow::on_answerButton_12_clicked()
{
    checkAnswer(4);
}
void MainWindow::on_cancelButton_2_clicked()
{
    on_mainpageButton_clicked();
}



void MainWindow::on_bkgdMusicVolumeSlider_valueChanged(int value)
{
    bkgdMusicValue = value;
    mediaPlayer->setVolume(bkgdMusicValue);
}

void MainWindow::on_musicPlayerVolumeSlider_valueChanged(int value)
{
    musicPlayerValue = value;
}

void MainWindow::on_rulesButton_clicked()
{
    bool check = true;
    if (checkInGame)
    {
        check = QMessageBox::warning(0,
                                     "Внимание!",
                                     "Вы потеряете игровой процесс."
                                     "\nОткрыть словарь ?",
                                     "Нет",
                                     "Да",
                                     QString(),
                                     0,
                                     1
                                    );

    }
    if (check)
    {
        tmr->stop();
        tmr_btn->stop();
        tmr_end->stop();
        if (checkInGame){
            checkInGame = false;
            backgroundMusic();            
            hideScoreInfo();
            removeEventFilterOnBtns();
        }
        sWindow->show();
        showUserInfo();
        hideLoginButtons();

        hideSpecialButtons();


    }

}

void MainWindow::statsOut()
{
    ui->statBrowser->clear();
    ui->statBrowser->insertHtml("<p style=\"font-size: 26px; padding: 30px 10px 10px 10px;\"><center><b>Статистика</b></center></p>");
    QSqlQuery query = game.getStats();

    QString html;
    html = "<center><table width=\"470\"><tr><td style=\"padding: 10px 0px 0px 10px\" width=\"120\"><b>Игрок</b></td><td style=\"padding: 10px 0px 0px 5px\"><b>Аудирование</b></td>"
           "<td style=\"padding: 10px 0px 0px 5px\"><b>Слова по картинке</b></td><td style=\"padding: 10px 0px 0px 5px\"><b>Грамматика</b></td><td style=\"padding: 10px 0px 0px 5px\"><b>Всего</b></td></tr>";

    while (query.next())
        {
        QString login = query.value(0).toString();
        QString music_score = query.value(1).toString();
        QString film_score = query.value(2).toString();
        QString gram_score = query.value(3).toString();
        int total = music_score.toInt() + film_score.toInt()+ gram_score.toInt();
        html += "<tr><td style=\"padding: 5px 0px 0px 10px\">" + login + "</td><td style=\"padding: 5px 0px 0px 5px\">" +
                music_score + "</td><td style=\"padding: 5px 0px 0px 5px\">" +
                film_score + "</td><td style=\"padding: 5px 0px 0px 5px\">" +
                gram_score + "</td><td style=\"padding: 5px 0px 0px 5px\">" +
                QString::number(total) + "</td></tr>";
        }
    html += "</table></center>";
    ui->statBrowser->insertHtml(html);
}

void MainWindow::updatePlayScreen()
{
    if(!game.playGame(actualGame)){
        playerWin();
    }
    else
    {
        tmr_btn->setInterval(5000);
        if (actualGame == "music"){
            mediaPlayer->setMedia(QUrl::fromLocalFile("/Users/user/Downloads/music/"+
                                                      game.getRightAnswerId(actualGame) + ".mp3"));
            mediaPlayer->setVolume(musicPlayerValue);
            mediaPlayer->setPosition(0);
            mediaPlayer->play();
            ui->countRightAnswers->setText(game.getRightAnswerCount(actualGame));
            ui->answerButton_1->setText(game.getAnswer(actualGame, 1));
            ui->answerButton_2->setText(game.getAnswer(actualGame, 2));
            ui->answerButton_3->setText(game.getAnswer(actualGame, 3));
            ui->answerButton_4->setText(game.getAnswer(actualGame, 4));
        }
        else
        if (actualGame == "films")

        {
            ui->filmLabel->setPixmap(QPixmap("/Users/user/Downloads/films/" +
                                             game.getRightAnswerId(actualGame) + ".jpg"));
            ui->filmLabel->setScaledContents(true);
            ui->filmLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

            ui->countRightAnswers->setText(game.getRightAnswerCount(actualGame));
            ui->answerButton_5->setText(game.getAnswer(actualGame, 1));
            ui->answerButton_6->setText(game.getAnswer(actualGame, 2));
            ui->answerButton_7->setText(game.getAnswer(actualGame, 3));
            ui->answerButton_8->setText(game.getAnswer(actualGame, 4));
        }
        else
             if (actualGame == "gram")
        {
            ui->gramLabel->setPixmap(QPixmap("/Users/user/Desktop/french/french/gram/" +
                                             game.getRightAnswerId(actualGame) + ".jpg"));
            ui->gramLabel->setScaledContents(true);
            ui->gramLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

            ui->countRightAnswers->setText(game.getRightAnswerCount(actualGame));
            ui->answerButton_9->setText(game.getAnswer(actualGame, 1));
            ui->answerButton_10->setText(game.getAnswer(actualGame, 2));
            ui->answerButton_11->setText(game.getAnswer(actualGame, 3));
            ui->answerButton_12->setText(game.getAnswer(actualGame, 4));
        }
        ui->secondsLabel->setText(QString::number(seconds = maxSeconds));
    }
}

void MainWindow::checkAnswer(int id)
{
    if (game.checkAnswerId(actualGame, id-1)){
        changeCurrentScore(game.getCurrentScore() + game.calculateScore((maxSeconds - seconds + 1), actualGame));
        updatePlayScreen();

    }
    else
    {
        if (actualGame == "music")
            playerLose("<table width=\"490\"><tr><td style=\"padding: 140px 10px 10px 10px;\"><center>Неверный ответ!<br>Это был трек \""
                       + game.getRightAnswerNameStr(actualGame) + "\".<br><br>Ваш счет: "+QString::number(game.getCurrentScore())
                       +"</center></td></tr></table>");
        else
            if (actualGame == "films")
            playerLose("<table width=\"490\"><tr><td style=\"padding: 140px 10px 10px 10px;\"><center>Неверный ответ!<br>Это был фильм \""
                       + game.getRightAnswerNameStr(actualGame) + "\".<br><br>Ваш счет: "+QString::number(game.getCurrentScore())
                       +"</center></td></tr></table>");
        else
                if (actualGame == "gram")
                playerLose("<table width=\"490\"><tr><td style=\"padding: 140px 10px 10px 10px;\"><center>Неверный ответ!<br>Это был фильм \""
                           + game.getRightAnswerNameStr(actualGame) + "\".<br><br>Ваш счет: "+QString::number(game.getCurrentScore())
                           +"</center></td></tr></table>");

    }
}

void MainWindow::backgroundMusic()
{
    mediaPlaylist->clear();
    QDir dir(QApplication::applicationDirPath()+"/res/background_music/");
    if (dir.exists())
    {
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::IgnoreCase);
        QFileInfoList list = dir.entryInfoList();
        std::random_shuffle(list.begin(), list.end());

        for (int i = 0; i < list.size(); ++i)
        {
            QFileInfo fileInfo = list.at(i);
            mediaPlaylist->addMedia(QUrl::fromLocalFile(QApplication::applicationDirPath()+
                                                        "/res/background_music/"+
                                                        fileInfo.fileName()));
        }
    }
    mediaPlayer->setPlaylist(mediaPlaylist);
    mediaPlayer->setVolume(bkgdMusicValue);
    mediaPlayer->play();
}

void MainWindow::setNameAndScore()
{
    ui->name->setText("<html><head/><body><p align=\"center\">"
            "<span style=\" font-size:18pt; color:#6aaa49;\">" +
            game.getPlayer().getName() +
            "</span></p></body></html>");

    ui->score->setText("<html><head/><body><p align=\"center\">"
            "<span style=\" font-size:18pt; color:#ffffff;\">" +
            QString::number(game.getPlayer().getSumScore()) +
            "</span></p></body></html>");
    ui->countRightAnswers->setText("0");
    ui->secondsLabel->setText("0");
}

void MainWindow::updateTimer()
{
    if (seconds == 0)
        playerLose("<table width=\"490\"><tr><td style=\"padding: 170px 10px 10px 10px;\">"
                   "<center>Закончилось время!<br>Ваш счет: "+QString::number(game.getCurrentScore())
                   +"</center></td></tr></table>");
    ui->secondsLabel->setText(QString::number(seconds--));
}

void MainWindow::updateButton()
{    
    tmr_btn->start(100);
    QFont font("Comic Sans MC", 16);
    QFontMetrics fm(font);
    if (buttonToUpd->objectName() == "answerButton_1"){
        if (fm.width(ui->answerButton_1->text()) <= lenBtn){
            tmr_btn->stop();
            ui->answerButton_1->setText(game.getAnswer(actualGame, 1));
            tmr_btn->start(3000);
        }
        else
            ui->answerButton_1->setText(ui->answerButton_1->text().remove(0,1));
    }
    if (buttonToUpd->objectName() == "answerButton_2"){
        if (fm.width(ui->answerButton_2->text()) <= lenBtn){
            tmr_btn->stop();
            ui->answerButton_2->setText(game.getAnswer(actualGame, 2));
            tmr_btn->start(3000);
        }
        else
            ui->answerButton_2->setText(ui->answerButton_2->text().remove(0,1));
    }
    if (buttonToUpd->objectName() == "answerButton_3"){
        if (fm.width(ui->answerButton_3->text()) <= lenBtn){
            tmr_btn->stop();
            ui->answerButton_3->setText(game.getAnswer(actualGame, 3));
            tmr_btn->start(3000);
        }
        else
            ui->answerButton_3->setText(ui->answerButton_3->text().remove(0,1));
    }
    if (buttonToUpd->objectName() == "answerButton_4"){
        if (fm.width(ui->answerButton_4->text()) <= lenBtn){
            tmr_btn->stop();
            ui->answerButton_4->setText(game.getAnswer(actualGame, 4));
            tmr_btn->start(3000);
        }
        else
            ui->answerButton_4->setText(ui->answerButton_4->text().remove(0,1));
    }
    if (buttonToUpd->objectName() == "answerButton_5"){
        if (fm.width(ui->answerButton_5->text()) <= lenBtn){
            tmr_btn->stop();
            ui->answerButton_5->setText(game.getAnswer(actualGame, 1));
            tmr_btn->start(3000);
        }
        else
            ui->answerButton_5->setText(ui->answerButton_5->text().remove(0,1));
    }
    if (buttonToUpd->objectName() == "answerButton_6"){
        if (fm.width(ui->answerButton_6->text()) <= lenBtn){
            tmr_btn->stop();
            ui->answerButton_6->setText(game.getAnswer(actualGame, 2));
            tmr_btn->start(3000);
        }
        else
            ui->answerButton_6->setText(ui->answerButton_6->text().remove(0,1));
    }
    if (buttonToUpd->objectName() == "answerButton_7"){
        if (fm.width(ui->answerButton_7->text()) <= lenBtn){
            tmr_btn->stop();
            ui->answerButton_7->setText(game.getAnswer(actualGame, 3));
            tmr_btn->start(3000);
        }
        else
            ui->answerButton_7->setText(ui->answerButton_7->text().remove(0,1));
    }
    if (buttonToUpd->objectName() == "answerButton_8")
    {
        if (fm.width(ui->answerButton_8->text()) <= lenBtn)
        {
            tmr_btn->stop();
            ui->answerButton_8->setText(game.getAnswer(actualGame, 4));
            tmr_btn->start(3000);
        }
        else
            ui->answerButton_8->setText(ui->answerButton_8->text().remove(0,1));
    }
    if (buttonToUpd->objectName() == "answerButton_8")
    {
        if (fm.width(ui->answerButton_9->text()) <= lenBtn)
        {
            tmr_btn->stop();
            ui->answerButton_9->setText(game.getAnswer(actualGame, 1));
            tmr_btn->start(3000);
        }
        else
            ui->answerButton_9->setText(ui->answerButton_9->text().remove(0,1));
    }
    if (buttonToUpd->objectName() == "answerButton_10")
    {
        if (fm.width(ui->answerButton_10->text()) <= lenBtn)
        {
            tmr_btn->stop();
            ui->answerButton_10->setText(game.getAnswer(actualGame, 2));
            tmr_btn->start(3000);
        }
        else
            ui->answerButton_10->setText(ui->answerButton_10->text().remove(0,1));
    }
    if (buttonToUpd->objectName() == "answerButton_11")
    {
        if (fm.width(ui->answerButton_11->text()) <= lenBtn)
        {
            tmr_btn->stop();
            ui->answerButton_11->setText(game.getAnswer(actualGame, 3));
            tmr_btn->start(3000);
        }
        else
            ui->answerButton_11->setText(ui->answerButton_11->text().remove(0,1));
    }
    if (buttonToUpd->objectName() == "answerButton_12")
    {
        if (fm.width(ui->answerButton_12->text()) <= lenBtn)
        {
            tmr_btn->stop();
            ui->answerButton_12->setText(game.getAnswer(actualGame, 4));
            tmr_btn->start(3000);
        }
        else
            ui->answerButton_12->setText(ui->answerButton_12->text().remove(0,1));
    }
}

void MainWindow::returnButton()
{
    tmr_btn->stop();
    if(actualGame == "music")
    {
        ui->answerButton_1->setText(game.getAnswer(actualGame, 1));
        ui->answerButton_2->setText(game.getAnswer(actualGame, 2));
        ui->answerButton_3->setText(game.getAnswer(actualGame, 3));
        ui->answerButton_4->setText(game.getAnswer(actualGame, 4));
    }
    else
        if(actualGame == "films")
    {
        ui->answerButton_5->setText(game.getAnswer(actualGame, 1));
        ui->answerButton_6->setText(game.getAnswer(actualGame, 2));
        ui->answerButton_7->setText(game.getAnswer(actualGame, 3));
        ui->answerButton_8->setText(game.getAnswer(actualGame, 4));
    }
    else
        {
            ui->answerButton_9->setText(game.getAnswer(actualGame, 1));
            ui->answerButton_10->setText(game.getAnswer(actualGame, 2));
            ui->answerButton_11->setText(game.getAnswer(actualGame, 3));
            ui->answerButton_12->setText(game.getAnswer(actualGame, 4));
        }

}

void MainWindow::howtoOut()
{
    ui->howtoBrowser->clear();
    QFile file(":/text/res/how_to_play.txt");
    if (!file.open(QIODevice::ReadOnly))
        return;
    else
    {
         ui->howtoBrowser->insertHtml(QString::fromUtf8(file.readAll()));
    }
}

void MainWindow::aboutOut()
{
    ui->aboutBrowser->clear();
    QFile file(":/text/res/about.txt");
    if (!file.open(QIODevice::ReadOnly))
        return;
    else
    {
         ui->aboutBrowser->insertHtml(QString::fromUtf8(file.readAll()));
    }
}

void MainWindow::playerLose(QString message)
{
    checkInGame = false;

    if (actualGame == "music")
    {
        if (game.getPlayer().getMusicScore() < game.getCurrentScore()){
            game.setPlayerScore(game.getCurrentScore(), actualGame);
            game.changeScoreInDB(actualGame, game.getCurrentScore());
        }
    }else
        if (actualGame == "films")
    {
        if (game.getPlayer().getFilmScore() < game.getCurrentScore())
        {
            game.setPlayerScore(game.getCurrentScore(), actualGame);
            game.changeScoreInDB(actualGame, game.getCurrentScore());
        }
    }
        else
            if (actualGame == "gram")
        {
            if (game.getPlayer().getGramScore() < game.getCurrentScore())
            {
                game.setPlayerScore(game.getCurrentScore(), actualGame);
                game.changeScoreInDB(actualGame, game.getCurrentScore());
            }
        }
    backgroundMusic();
    on_statButton_clicked();
    ui->tryagainButton->show();
    ui->statBrowser->clear();
    ui->statBrowser->insertHtml(message);
    tmr_end->start();
    tmr->stop();
}

void MainWindow::playerWin()
{
    checkInGame = false;

    if (actualGame == "music")
    {
        if (game.getPlayer().getMusicScore() < game.getCurrentScore()){
            game.getPlayer().setMusicScore(game.getCurrentScore());
            game.changeScoreInDB(actualGame, game.getCurrentScore());
        }
    }else
        if (actualGame == "films")

    {
        if (game.getPlayer().getFilmScore() < game.getCurrentScore()){
            game.getPlayer().setFilmScore(game.getCurrentScore());
            game.changeScoreInDB(actualGame, game.getCurrentScore());
        }
    }
    else
            if (actualGame == "gram")
        {
            if (game.getPlayer().getGramScore() < game.getCurrentScore()){
                game.getPlayer().setGramScore(game.getCurrentScore());
                game.changeScoreInDB(actualGame, game.getCurrentScore());
            }
        }
    backgroundMusic();
    on_statButton_clicked();
    ui->tryagainButton->show();
    ui->statBrowser->clear();
    ui->statBrowser->insertHtml("<table width=\"490\"><tr><td style=\"padding: 170px 10px 10px 10px;\"><center>Вы выиграли!</center></td></tr></table>");
    if (actualGame == "music")
        ui->countRightAnswers->setText(QString::number((game.getRightAnswerCount(actualGame)).toInt()+1));
    else
        if (actualGame == "films")
        ui->countRightAnswers->setText(QString::number((game.getRightAnswerCount(actualGame)).toInt()+1));
    else
        if (actualGame == "gram")
        ui->countRightAnswers->setText(QString::number((game.getRightAnswerCount(actualGame)).toInt()+1));
    tmr->stop();
    tmr_end->start();
}

void MainWindow::gameEnd()
{
    checkInGame = false;
    on_statButton_clicked();
    ui->tryagainButton->show();
    hideScoreInfo();
}

void MainWindow::resizeBtnUp()
{
    if (actualBtn == "music")
        if(sizeBtn<=190)
        {
            ui->playMusic->setFixedHeight(sizeBtn);
            ui->playMusic->setFixedWidth(sizeBtn);
            tmr_mainUp->start(40);
            sizeBtn+=2;
        }
        else
        {
            tmr_mainUp->stop();
            tmr_mainDown->start();
        }
    else
        if (actualBtn == "films")
        if(sizeBtn<=190)
        {
            ui->playFilm->setFixedHeight(sizeBtn);
            ui->playFilm->setFixedWidth(sizeBtn);
            tmr_mainUp->start(40);
            sizeBtn+=2;
        }
        else
        {
            tmr_mainUp->stop();
            tmr_mainDown->start();
        }
    else
            if (actualBtn == "gram")
            if(sizeBtn<=190)
            {
                ui->playFilm->setFixedHeight(sizeBtn);
                ui->playFilm->setFixedWidth(sizeBtn);
                tmr_mainUp->start(40);
                sizeBtn+=2;
            }
            else
            {
                tmr_mainUp->stop();
                tmr_mainDown->start();
            }
}

void MainWindow::resizeBtnDown()
{
    if (actualBtn == "music")
        if(sizeBtn>=170)
        {
            ui->playMusic->setFixedHeight(sizeBtn);
            ui->playMusic->setFixedWidth(sizeBtn--);
            tmr_mainDown->start(40);
            sizeBtn-=2;
        }
        else
        {
            tmr_mainDown->stop();
            tmr_mainUp->start(300);
            actualBtn = "film";
        }
    else
        if (actualBtn == "film")
        if(sizeBtn>=170)
        {
            ui->playFilm->setFixedHeight(sizeBtn);
            ui->playFilm->setFixedWidth(sizeBtn--);
            tmr_mainDown->start(40);
            sizeBtn-=2;
        }
        else
        {
            tmr_mainDown->stop();
            tmr_mainUp->start(3000);
            actualBtn = "gram";
        }
    else
            if (actualBtn == "gram")
            if(sizeBtn>=170)
            {
                ui->playGram->setFixedHeight(sizeBtn);
                ui->playGram->setFixedWidth(sizeBtn--);
                tmr_mainDown->start(40);
                sizeBtn-=2;
            }
            else
            {
                tmr_mainDown->stop();
                tmr_mainUp->start(3000);
                actualBtn = "music";
            }


        }

void MainWindow::on_tryagainButton_clicked()
{
    tmr_end->stop();
    if (actualGame == "music")
        on_playMusic_clicked();
    else
        if (actualGame == "films")
        on_playFilm_clicked();
    else
if (actualGame == "gram")
        on_playGram_clicked();
}

void MainWindow::changeCurrentScore(int value)
{
    game.setCurrentScore(value);
    ui->score->setText("<html><head/><body><p align=\"center\">"
                       "<span style=\" font-size:18pt; color:#ffffff;\">" +
                       QString::number(game.getCurrentScore()) +
                       "</span></p></body></html>");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    bool check = true;
    if (checkInGame)
    {
        check = QMessageBox::warning(0,
                                     "Внимание!",
                                     "Вы потеряете игровой процесс."
                                     "\nВыйти из игры?",
                                     "Нет",
                                     "Да",
                                     QString(),
                                     0,
                                     1
                                    );
    }
    if (!check)
            event->ignore();
        else
    {
        event->accept();
        game.changeScoreInDB("music", game.getPlayer().getMusicScore());
        game.changeScoreInDB("film", game.getPlayer().getFilmScore());
        game.changeScoreInDB("gram", game.getPlayer().getGramScore());
    }
}

void MainWindow::on_levelDiffSlider_valueChanged(int value)
{
    switch (value)
      {
         case 1:
         {
            maxSeconds = MAX_SECONDS_EASY;
            break;
         }
         case 2:
         {
            maxSeconds = MAX_SECONDS_MIDDLE;
            break;
         }
         case 3:
         {
            maxSeconds = MAX_SECONDS_DIFFICULT;
            break;
         }
      }
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if ((obj == (QObject*)ui->answerButton_1)||
            (obj == (QObject*)ui->answerButton_2)||
            (obj == (QObject*)ui->answerButton_3)||
            (obj == (QObject*)ui->answerButton_4)||
            (obj == (QObject*)ui->answerButton_5)||
            (obj == (QObject*)ui->answerButton_6)||
            (obj == (QObject*)ui->answerButton_7)||
            (obj == (QObject*)ui->answerButton_8)||
            (obj == (QObject*)ui->answerButton_9)||
            (obj == (QObject*)ui->answerButton_10)||
            (obj == (QObject*)ui->answerButton_11)||
            (obj == (QObject*)ui->answerButton_12)||
            (obj == (QObject*)ui->pageMusic)||
            (obj == (QObject*)ui->pageFilm)||
            (obj == (QObject*)ui->pageGram))
    {
        if (event->type() == QEvent::HoverEnter)
        {
            buttonToUpd = obj;
            updateButton();
        }
        if (event->type() == QEvent::HoverLeave)
        {
            returnButton();
        }
        return QWidget::eventFilter(obj, event);
}
    else
    {
        return QWidget::eventFilter(obj, event);
    }
}


