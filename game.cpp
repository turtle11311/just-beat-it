#include "game.h"
#include "ui_game.h"
#include <QProcess>
#include <QFileInfo>
#include <QAudioProbe>
#include <QTimer>
#include <pthread.h>
#include "properties.h"

extern Properties properties;

void *detectSpectrum( void *ptr )
{
    Game *w = (Game*)ptr;
    int now = 0;
    QQueue<int> beatTime(properties.beats);
    while( !beatTime.isEmpty() )
    {
        now = w->musicPlayer->position();
        if( !beatTime.isEmpty() && beatTime.head() < now )
        {
            w->lastBeat = beatTime.head();
            w->ui->spectrum->setText(w->direction.mid(beatTime.dequeue() % 4, 1));
        }
    }
    return NULL;
}

void *communication( void *ptr )
{
    Game *w = (Game*)ptr;
    QString message;
    QQueue<int> beatTime(properties.beats);
    int next = 5000;
    int end = beatTime.last();
    try
    {
        while (!beatTime.isEmpty()) {
            int now = w->lastBeat;
            if(next < now || now == end)
            {
                message = "BEAT:" + QString::number(next) + ":";
                while( !beatTime.isEmpty() && beatTime.head() < next )
                {
                    if(w->hitBuffer.contains(beatTime.head()))
                    {
                        if( message.right(1) != ":" )
                            message += ",";
                        message += ( QString::number(beatTime.head()) + "," + QString::number(w->hitBuffer[beatTime.head()]) );
                    }
                    beatTime.dequeue();
                }
                qDebug() << message << " " << message.length();
                w->socket.Send(message);
                message =  w->socket.Recv(1024);
                qDebug() << message << " " << message.length();
                QVector<QString> detail = message.split(",").toVector();
                for( int i = 0 ; i < detail.length() ; i += 2 )
                {
                    qDebug() <<detail[i]<<detail[i].leftJustified(15,' ') + detail[i+1].rightJustified(10,' ');
                    properties.scores[detail[i]].insert(next,detail[i+1].toInt());
                    w->scoreBoard[i/2]->setText(detail[i].leftJustified(15,' ') + detail[i+1].rightJustified(10,' '));
                }
                w->ui->score->setText("+" + QString::number(properties.scores[properties.account][next] - properties.scores[properties.account][next - 5000]));
                next += 5000;
            }
        }
        w->socket.Send("FINISH");
        do
        {
            message = w->socket.Recv(1024);
            qDebug() << message << " " << message.length();
            QVector<QString> detail = message.split(",").toVector();
            for( int i = 1 ; i < detail.length() ; i += 2 )
                properties.hits[detail[0]].insert(detail[i].toInt(),detail[i+1].toInt());
            w->socket.Send("OK");
        }while(message != "FINISH");
        w->socket.Send("CLOSE");
        w->socket.Close();
    }
    catch(SocketException ex)
    {
        qDebug() << ex.message;
    }
    emit w->finish();
    return NULL;
}

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    try
    {
        ui->setupUi(this);

        direction = "▲▼◀▶";
        lastBeat = 0;

        connect(this,SIGNAL(finish()),parent,SLOT(scoreboard()));

        musicPlayer = new QMediaPlayer(this);
        beatPlayer = new QMediaPlayer(this);
        musicPlayer->setVolume(ui->musicVolumn->value());
        beatPlayer->setVolume(ui->beatVolumn->value());

        scoreBoard[0] = ui->p1;
        scoreBoard[1] = ui->p2;
        scoreBoard[2] = ui->p3;
        scoreBoard[3] = ui->p4;
        QMap<QString,QMap<int,int>>::iterator it = properties.scores.begin();
        for( int i = 0 ; i < 4 ; i++ )
        {
            if(i <properties.scores.size())
            {
                scoreBoard[i]->setVisible(true);
                scoreBoard[i]->setText(it.key().leftJustified(24,' ') + "0");
                it++;
            }
            else
            {
                scoreBoard[i]->setVisible(false);
            }
        }

        QString message;

        socket.Connect();

        socket.Send("JOIN:" + properties.room + ":" + properties.account);
        message =  socket.Recv(1024);
        qDebug() << message << " " << message.length();
        if(message == "NO")
            throw SocketException("Can not start the game");

        QFileInfo *music = new QFileInfo( "./sources/music/" + properties.musicID + ".wav" );
        QFileInfo *beat = new QFileInfo( "./sources/music/" + properties.musicID + "-beat.wav" );
        QProcess *process = new QProcess(this);
        if( !music->exists() )
        {
            process->start("./sources/tools/youtube-dl" , QStringList() << "-o" << "./sources/music/" + properties.musicID + ".%(ext)s" << "-x" << "--audio-format" << "wav" << "https://youtu.be/" + properties.musicID );
            process->waitForFinished();
            if ( process->exitCode() != 0 )
            {
                qWarning() << "Error:" << process->errorString();
                return;
            }
        }

        process->start("./sources/tools/beat.sh" , QStringList() << properties.musicID);
        process->waitForFinished();
        if ( process->exitCode() != 0 )
        {
            qWarning() << "Error:" << process->errorString();
            return;
        }
        QFile file("./sources/music/" + properties.musicID + "-beat.txt");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<<"Can't open the file!"<<endl;
        }
        properties.beats.clear();
        hitBuffer.clear();
        lastBeat = 0;
        while(!file.atEnd()) {
            QByteArray line = file.readLine();
            QString str(line);
            properties.beats.enqueue(str.toDouble() * 1000);
        }

        musicPlayer->setMedia(QUrl::fromLocalFile(music->absoluteFilePath()));
        beatPlayer->setMedia(QUrl::fromLocalFile(beat->absoluteFilePath()));
        QAudioProbe *audioProbe = new QAudioProbe();
        if (audioProbe->setSource(musicPlayer)) {
            connect(audioProbe, SIGNAL(audioBufferProbed(QAudioBuffer)), ui->widget, SLOT(processBuffer(QAudioBuffer)));
        }
        this->setFocus();

        socket.Send("READY");
        message =  socket.Recv(1024);
        qDebug() << message << " " << message.length();

        musicPlayer->play();
        beatPlayer->play();
        pthread_t thread1,thread2;
        pthread_create(&thread1, NULL , detectSpectrum , (void*) this);
        pthread_create(&thread2, NULL , communication , (void*) this);
    }
    catch(SocketException ex)
    {
        qDebug() << ex.message;
    }

}

Game::~Game()
{
    delete ui;
}

void Game::on_musicVolumn_valueChanged(int value)
{
    musicPlayer->setVolume(value);
    this->setFocus();
}

void Game::on_beatVolumn_valueChanged(int value)
{
    beatPlayer->setVolume(value);
    this->setFocus();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    int pos = musicPlayer->position();
    int hit = -1;
    if(musicPlayer->state() == QMediaPlayer::PlayingState && pos - lastBeat < 1000 && properties.beats.contains( lastBeat ) && !hitBuffer.contains(lastBeat))
    {
        switch (event->key())
        {
        case Qt::Key_Up:
            hit = 0;
            break;
        case Qt::Key_Down:
            hit = 1;
            break;
        case Qt::Key_Left:
            hit = 2;
            break;
        case Qt::Key_Right:
            hit = 3;
            break;
        case Qt::Key_Space:
            hit = lastBeat % 4;
            break;
        default:
            hit = -1;
            break;
        }
        if( lastBeat % 4 == hit )
        {
            hitBuffer.insert(lastBeat,pos);
        }
   }
}
