#ifndef SELECTMUSIC_H
#define SELECTMUSIC_H

#include <QWidget>
#include <QStringListModel>
#include "youtubesearch.h"
#include "youtubemedialistmodel.h"

namespace Ui {
class SelectMusic;
}

class SelectMusic : public QWidget
{
    Q_OBJECT

public:
    explicit SelectMusic(QWidget *parent = 0);
    ~SelectMusic();

private slots:
    void on_searchButton_clicked();

private:
    Ui::SelectMusic *ui;
    YoutubeSearch *yt;
    YoutubeMediaListModel *ylist;
    QStringListModel *listModel;
};

#endif // SELECTMUSIC_H
