#include "scoreboard.h"
#include "ui_scoreboard.h"
#include <QFileInfo>
#include <QDebug>
#include <pthread.h>
#include "properties.h"

extern Properties properties;

void *setSpectrum( void *ptr )
{
    ScoreBoard *w = (ScoreBoard*)ptr;
    QVector<int> beatTime(properties.beats.toVector());
    int now = 0;
    int pos = 0;
    while( !w->exit )
    {
        now = w->musicPlayer->position();
        if(w->reset)
        {
            pos = 0;
            w->ui->spectrum->setText("");
            w->reset = false;
        }
        while( pos < beatTime.size() - 1 && beatTime[pos] < now )
        {
            w->ui->spectrum->setText(w->direction.mid(beatTime[pos++] % 4, 1));
        }
    }
    emit w->finish();
    return NULL;
}

ScoreBoard::ScoreBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreBoard)
{
    ui->setupUi(this);

    direction = "▲▼◀▶";
    reset = false;
    exit = false;


    scoreBoard[0] = ui->p1;
    scoreBoard[1] = ui->p2;
    scoreBoard[2] = ui->p3;
    scoreBoard[3] = ui->p4;

    crowns[0] = ui->crown1;
    crowns[1] = ui->crown2;
    crowns[2] = ui->crown3;
    crowns[3] = ui->crown4;

    QMap<int,QString> orders;
    for(QString id : properties.scores.keys())
    {
        orders.insert(properties.scores[id].last(),id);
    }
    int max = orders.lastKey();
    QMap<int,QString>::iterator it = orders.begin();
    for( int i = 3 ; i >= 0 ; i-- )
    {
        if(i < orders.size())
        {
            scoreBoard[i]->setVisible(true);
            crowns[i]->setVisible(it.key()==max);
            scoreBoard[i]->setText(it.value().leftJustified(15,' ') + QString::number(it.key()).rightJustified(10,' '));
            it++;
        }
        else
        {
            scoreBoard[i]->setVisible(false);
            crowns[i]->setVisible(false);
        }
    }

    QFileInfo *music = new QFileInfo( "./sources/music/" + properties.musicID + ".wav" );
    QFileInfo *beat = new QFileInfo( "./sources/music/" + properties.musicID + "-beat.wav" );
    musicPlayer = new QMediaPlayer(this);
    beatPlayer = new QMediaPlayer(this);
    connect(musicPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(setTime(qint64)));
    connect(musicPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(setTime(qint64)));
    connect(musicPlayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(setState(QMediaPlayer::State)));
    musicPlayer->setMedia(QUrl::fromLocalFile(music->absoluteFilePath()));
    beatPlayer->setMedia(QUrl::fromLocalFile(beat->absoluteFilePath()));
    musicPlayer->setVolume(ui->musicVolumn->value());
    beatPlayer->setVolume(ui->beatVolumn->value());

    connect(this,SIGNAL(finish()),parent,SLOT(backRoom()));
    pthread_t thread1;
    pthread_create(&thread1, NULL , setSpectrum , (void*) this);

}

ScoreBoard::~ScoreBoard()
{
    delete ui;
}

void ScoreBoard::on_musicVolumn_valueChanged(int value)
{
    musicPlayer->setVolume(value);
}

void ScoreBoard::on_beatVolumn_valueChanged(int value)
{
    beatPlayer->setVolume(value);
}

void ScoreBoard::setTime(qint64)
{
    int now = musicPlayer->position() > 0 ? musicPlayer->position() / 1000 : 0;
    int len = musicPlayer->duration() > 0 ? musicPlayer->duration() / 1000 : 0;
    ui->time->setText(QString().sprintf("%02d:%02d  /  %02d:%02d" , now / 60 , now % 60 , len / 60 , len % 60));
    ui->timeSlider->setMaximum(musicPlayer->duration());
    ui->timeSlider->blockSignals(true);
    ui->timeSlider->setValue(musicPlayer->position());
    ui->timeSlider->blockSignals(false);
}

void ScoreBoard::setState(QMediaPlayer::State state)
{
    if(state==QMediaPlayer::PlayingState)
    {
        ui->playButton->setText("❚❚");
    }
    else
    {
        ui->playButton->setText("▶");
    }
}

void ScoreBoard::on_playButton_clicked()
{
    if(musicPlayer->state()==QMediaPlayer::PlayingState)
    {
        musicPlayer->pause();
        beatPlayer->pause();
    }
    else
    {
        musicPlayer->play();
        beatPlayer->play();
    }
}

void ScoreBoard::on_timeSlider_valueChanged(int value)
{
    musicPlayer->setPosition(value);
    beatPlayer->setPosition(value);
    reset = true;
}

void ScoreBoard::on_exitButton_clicked()
{
    exit = true;
}
