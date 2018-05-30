#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>
#include <QLabel>
#include <QMediaPlayer>

namespace Ui {
class ScoreBoard;
}

class ScoreBoard : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreBoard(QWidget *parent = 0);
    ~ScoreBoard();
    friend void *setSpectrum( void *ptr );

signals:
    void finish();

private slots:
    void on_musicVolumn_valueChanged(int value);
    void on_beatVolumn_valueChanged(int value);
    void setTime(qint64);
    void setState(QMediaPlayer::State state);
    void on_playButton_clicked();
    void on_timeSlider_valueChanged(int value);
    void on_exitButton_clicked();

private:
    Ui::ScoreBoard *ui;
    QMediaPlayer *musicPlayer;
    QMediaPlayer *beatPlayer;
    QLabel *scoreBoard[4];
    QLabel *crowns[4];    
    QString direction;
    bool reset;
    bool exit;
};

#endif // SCOREBOARD_H
