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

    void on_selectMusicButton_clicked();

private:
    Ui::SelectMusic *ui;
    YoutubeSearch *yt;
    YoutubeMediaListModel *mediaListModel;
};

#endif // SELECTMUSIC_H
