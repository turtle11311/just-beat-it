#ifndef YOUTUBEMEDIALISTMODEL_H
#define YOUTUBEMEDIALISTMODEL_H

#include <QAbstractListModel>
#include "mediainfo.h"
#include <QList>

class YoutubeMediaListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit YoutubeMediaListModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setMediaList(const QList<MediaInfo>& list);
private:
    QList<MediaInfo> mlst;
};

#endif // YOUTUBEMEDIALISTMODEL_H
