#ifndef MEDIAINFO_H
#define MEDIAINFO_H

#include <QObject>
#include <QJsonObject>
#include <QSize>
#include <QUrl>
#include <QMetaType>
#include <QPainter>
#include <QImage>

class MediaInfo : public QObject
{
    Q_OBJECT
public:
    explicit MediaInfo(QObject *parent = nullptr);
    explicit MediaInfo(const QJsonObject &jObj, QObject *parent = nullptr);
    MediaInfo(const MediaInfo& mediaInfo, QObject *parent = nullptr);
    const MediaInfo& operator=(const MediaInfo& rhs);
    inline QString title() const { return _title; }
    inline QString videoId() const { return _videoId; }
    inline QString channelTitle() const { return _channelTitle; }
    inline QString description() const { return _description; }
    void paint(QPainter *painter, const QRect &rect,
                   const QPalette &palette) const;
    QSize sizeHint() const;
signals:

public slots:

private:
    void loadImage(QUrl url);
    QString _title;
    QString _videoId;
    QString _channelTitle;
    QString _description;
    QImage thumbnail;
};

Q_DECLARE_METATYPE(MediaInfo);

#endif // MEDIAINFO_H
