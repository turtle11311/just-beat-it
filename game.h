#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QLabel>
#include <QMediaPlayer>
#include <QQueue>
#include <QMap>
#include <QKeyEvent>
#include "socket.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT


public:
    explicit Game(QWidget *parent = 0);
    ~Game();
    void keyPressEvent(QKeyEvent *event);
    friend void *detectSpectrum( void *ptr );
    friend void *communication( void *ptr );

signals:
    void finish();

private slots:
    void on_musicVolumn_valueChanged(int value);
    void on_beatVolumn_valueChanged(int value);

private:
    Ui::Game *ui;
    QMediaPlayer *musicPlayer;
    QMediaPlayer *beatPlayer;
    Socket socket;
    QLabel *scoreBoard[4];
    QString direction;
    int lastBeat;
    QMap<int,int> hitBuffer;

};

#endif // GAME_H
