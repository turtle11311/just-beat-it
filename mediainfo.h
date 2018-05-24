#ifndef MEDIAINFO_H
#define MEDIAINFO_H

#include <QObject>
#include <QJsonObject>

class MediaInfo : public QObject
{
    Q_OBJECT
public:
    explicit MediaInfo(const QJsonObject &jObj, QObject *parent = nullptr);
    explicit MediaInfo(const MediaInfo& mediaInfo, QObject *parent = nullptr);
    const MediaInfo& operator=(const MediaInfo& rhs);
    inline QString title() const { return _title; }
    inline QString videoId() const { return _videoId; }
    inline QString channelTitle() const { return _channelTitle; }
    inline QString description() const { return _description; }
signals:

public slots:

private:
    QString _title;
    QString _videoId;
    QString _channelTitle;
    QString _description;
};

#endif // MEDIAINFO_H
