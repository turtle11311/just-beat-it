#include "selectmusic.h"
#include "mainwindow.h"
#include "ui_selectmusic.h"

SelectMusic::SelectMusic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectMusic)
{
    ui->setupUi(this);
    listModel = new QStringListModel(this);
    ylist = new YoutubeMediaListModel(this);
}

SelectMusic::~SelectMusic()
{
    delete ui;
}

void SelectMusic::on_searchButton_clicked()
{
    QString text = ui->queryText->toPlainText();
    yt = new YoutubeSearch(text, "AIzaSyDt1RCrwqcxYTdr7uK5lICnURqczbYoTto", this);
    ylist->setMediaList(yt->search(30));
    ui->searchResultView->setModel(ylist);
}
