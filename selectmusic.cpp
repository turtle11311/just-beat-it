#include "selectmusic.h"
#include "mainwindow.h"
#include "ui_selectmusic.h"
#include "properties.h"
#include "mediaitemdelegate.h"
#include <QDebug>
#include <QMessageBox>
#include "mysql.h"

extern Properties properties;

SelectMusic::SelectMusic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectMusic)
{
    ui->setupUi(this);
    mediaListModel = new YoutubeMediaListModel(this);
    connect(ui->selectMusicButton,SIGNAL(clicked()),parent,SLOT(formClose()));
    ui->searchResultView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->searchResultView->setItemDelegate(new MediaItemDelegate(this));
}

SelectMusic::~SelectMusic()
{
    delete ui;
}

void SelectMusic::on_searchButton_clicked()
{
    QString text = ui->queryText->toPlainText();
    yt = new YoutubeSearch(text, "AIzaSyDt1RCrwqcxYTdr7uK5lICnURqczbYoTto", this);
    mediaListModel->setMediaList(yt->search(10));
    ui->searchResultView->setModel(mediaListModel);
}

void SelectMusic::on_selectMusicButton_clicked()
{
    MediaInfo info = qvariant_cast<MediaInfo>(ui->searchResultView->currentIndex().data());
    properties.musicID = info.videoId();
    properties.music = info.title();
    try
    {
        MySQL db;
        db.Query("UPDATE room SET music=?, mucicID=? WHERE p1=?",
                 QVector<QVariant>{ properties.music, properties.musicID, properties.account });
    }
    catch(SQLException ex)
    {
        QMessageBox::critical(this,"Database Error",ex.message);
    }
    qDebug() << "Select: " << info.title() << ", " << info.videoId();
}
