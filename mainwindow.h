#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <game.h>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/qmediaplayer.h>
#include <QMediaPlaylist>
#include <QFile>
#include <QTimer>
#include <QDir>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QFontMetrics>
#include "sets.h"

const int MAX_SECONDS_EASY = 30;
const int MAX_SECONDS_MIDDLE = 15;
const int MAX_SECONDS_DIFFICULT = 5;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_playMusic_clicked();
    void on_playFilm_clicked();
    void on_playGram_clicked();
    void on_mainpageButton_clicked();
    void on_statButton_clicked();
   void on_loginButton_clicked();
    void on_loginButton_3_clicked();
    void on_signupButton_clicked();
    void on_signupButton_2_clicked();
    void on_cancelButton_clicked();
    void on_cancelButton_2_clicked();
 //   void on_settingsButton_clicked();
  //  void on_aboutButton_clicked();
    void on_rulesButton_clicked();
    void on_exitButton_clicked();

    void on_answerButton_1_clicked();
    void on_answerButton_2_clicked();
    void on_answerButton_3_clicked();
    void on_answerButton_4_clicked();
    void on_answerButton_5_clicked();
    void on_answerButton_6_clicked();
    void on_answerButton_7_clicked();
    void on_answerButton_8_clicked();
    void on_answerButton_9_clicked();
    void on_answerButton_10_clicked();
    void on_answerButton_11_clicked();
    void on_answerButton_12_clicked();
    void on_tryagainButton_clicked();

    void on_bkgdMusicVolumeSlider_valueChanged(int value);
    void on_musicPlayerVolumeSlider_valueChanged(int value);
    void on_levelDiffSlider_valueChanged(int value);

    void updateTimer();
    void updateButton();
    void returnButton();
    void gameEnd();
    void resizeBtnUp();
    void resizeBtnDown();



private:
    Ui::MainWindow *ui;
sets *sWindow;
    Game game;
    QMediaPlayer * mediaPlayer;
    QMediaPlaylist * mediaPlaylist;
    QGraphicsDropShadowEffect * shadowEffect;
    QTimer *tmr;
    QTimer *tmr_btn;
    QTimer *tmr_end;
    QTimer *tmr_mainUp;
    QTimer *tmr_mainDown;
    int bkgdMusicValue;
    int musicPlayerValue;
    int seconds;
    QString actualGame;
    bool checkInGame;
    int maxSeconds;
    int sizeBtn;
    QString actualBtn;
    int lenBtn;
    QObject *buttonToUpd;

    void hideUserInfo();
    void showUserInfo();
    void hideScoreInfo();
    void showScoreInfo();
    void hideSpecialButtons();
    void showSpecialButtons();
    void hideLoginButtons();
    void showLoginButtons();
    void installEventFilterOnBtns();
    void removeEventFilterOnBtns();

    void statsOut();
    void howtoOut();
    void aboutOut();
    void updatePlayScreen();
    void checkAnswer(int id);
    void backgroundMusic();
    void setNameAndScore();
    void playerLose(QString message);
    void playerWin();
    void changeCurrentScore(int value);

    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
