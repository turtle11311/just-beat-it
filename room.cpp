#include "room.h"
#include "mysql.h"
#include "properties.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "ui_room.h"

extern Properties properties;

Room::Room(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Room)
{
    ui->setupUi(this);
    QFont font;
    font = ui->leader->font();
    font.setCapitalization(QFont::AllUppercase);
    ui->leader->setFont(font);
    ui->refreshButton->setText("\xe2\x9f\xb3");
    refreshRoom();
    timer.setInterval(10);
    timer.setSingleShot(false);
    connect(&timer,SIGNAL(timeout()),this,SLOT(timeout()));    
    connect(ui->exitButton,SIGNAL(clicked()),parent,SLOT(formClose()));
    connect(ui->musicButton,SIGNAL(clicked()),parent,SLOT(selectMusic()));
    ui->players->setVisible(false);
}

Room::~Room()
{
    leave();
    delete ui;
}

void Room::leave()
{
    try
    {
        if(timer.isActive())timer.stop();
        ui->players->setVisible(false);
        if(!properties.room.isEmpty())
        {
            MySQL db;
            QString result = db.Query("select LeaveRoom( ? , ? )" , QVector<QVariant>{ properties.room , properties.account })[0][0].toString();
            if( result != "Success" )
            {
                QMessageBox::critical(this,"",result);
                return;
            }
            properties.room = "";
            properties.music = "";
            properties.musicID = "";
            ui->music->setText("歌曲 : ");
        }
        ui->leader->setText("");
        refreshRoom();
        ui->rooms->setEnabled(true);
    }
    catch(SQLException ex)
    {
        QMessageBox::critical(this,"Database Error",ex.message);
    }
}

void Room::refreshRoom()
{
    try
    {
        MySQL db;
        QVector<QVector<QVariant>> result = db.Query("select p1 from room where p1 like concat( ? , '%')" , QVector<QVariant>{ ui->leader->text() });
        QStringListModel* model = new QStringListModel(this);
        QStringList list;
        for( int i = 0 ; i < result.size() ; i++ )
        {
            list.append(result[i][0].toString());
        }
        model->setStringList(list);
        ui->roomList->setModel(model);
    }
    catch(SQLException ex)
    {
        QMessageBox::critical(this,"Database Error",ex.message);
    }
}

void Room::refreshPlayer()
{
    try
    {
        MySQL db;
        QVector<QVector<QVariant>> result = db.Query("select * from room where p1=?" , QVector<QVariant>{ properties.room });
        QStringListModel* model = new QStringListModel(this);
        QStringList list;
        for( int i = 0 ; i < 4 ; i++ )
        {
            list.append(result[0][i].toString());
        }
        model->setStringList(list);
        ui->playerList->setModel(model);
        ui->music->setVisible(true);
        if(!result[0][4].toString().isEmpty())
        {
            ui->music->setText("歌曲 : " + result[0][4].toString());
            properties.music = result[0][4].toString();
            properties.musicID = result[0][5].toString();
        }
        ui->leaveButton->setVisible(true);
        if(result[0][0].toString() == properties.account)
        {
            ui->musicButton->setVisible(true);
            ui->startButton->setVisible(true);
            ui->startButton->setEnabled(!properties.music.isEmpty());
        }
        else
        {
            ui->musicButton->setVisible(false);
            ui->startButton->setVisible(false);
        }
        ui->players->setVisible(true);
        if(result[0][6].toInt() == 1)
        {
            ui->music->setText("PLAY");
        }
    }
    catch(SQLException ex)
    {
        QMessageBox::critical(this,"Database Error",ex.message);
    }
}

void Room::on_roomList_doubleClicked(const QModelIndex &index)
{
    MySQL db;
    QString result = db.Query("select JoinRoom( ? , ? )" , QVector<QVariant>{ index.data().toString() , properties.account })[0][0].toString();
    if( result != "Success" )
    {
        QMessageBox::critical(this,"",result);
        return;
    }
    properties.room = index.data().toString();
    ui->leader->setText("");
    refreshRoom();
    ui->rooms->setEnabled(false);
    timer.start();
}

void Room::on_leader_textChanged(const QString &arg1)
{
    QString text = arg1.toUpper();
    QRegExp regex("^[A-Z0-9]{0,15}$");
    if(!regex.exactMatch(text))
    {
        text = text.left(text.size()-1);
        QMessageBox::critical(this,"","請輸入英文或數字");
    }
    ui->leader->setText(text);
    refreshRoom();
}

void Room::timeout()
{
    refreshPlayer();
}

void Room::on_createButton_clicked()
{
    try
    {
        MySQL db;
        db.Query("insert into room(p1) values(?)" , QVector<QVariant>{ properties.account });
        properties.room = properties.account;
        ui->leader->setText("");
        refreshRoom();
        ui->rooms->setEnabled(false);
        timer.start();
    }
    catch(SQLException ex)
    {
        QMessageBox::critical(this,"Database Error",ex.message);
    }
}

void Room::on_refreshButton_clicked()
{
    refreshRoom();
}

void Room::on_leaveButton_clicked()
{
    leave();
}

void Room::on_startButton_clicked()
{
    try
    {
        MySQL db;
        db.Query("update room set play=1 where p1=?" , QVector<QVariant>{ properties.account });
    }
    catch(SQLException ex)
    {
        QMessageBox::critical(this,"Database Error",ex.message);
    }
}
