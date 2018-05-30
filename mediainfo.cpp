#include "mediainfo.h"
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QDebug>

MediaInfo::MediaInfo(QObject *parent)
    : QObject(parent)
{

}

MediaInfo::MediaInfo(const QJsonObject& jObj, QObject *parent) : QObject(parent)
{
    QJsonObject snippet = jObj["snippet"].toObject();
    QJsonObject thumbnails = snippet["thumbnails"].toObject()["default"].toObject();\
    QString thumbnailUrl = thumbnails["url"].toString();
    //loadImage(QUrl(thumbnailUrl));
    _videoId = jObj["id"].toObject()["videoId"].toString();
    _title = snippet["title"].toString();
    _description = snippet["description"].toString();
    _channelTitle = snippet["channelTitle"].toString();
}

MediaInfo::MediaInfo(const MediaInfo &mediaInfo, QObject *parent)
    : QObject(parent),
      _title(mediaInfo._title),
      _videoId(mediaInfo._videoId),
      _channelTitle(mediaInfo._channelTitle),
      _description(mediaInfo._description),
      thumbnail(mediaInfo.thumbnail)
{
}

const MediaInfo& MediaInfo::operator=(const MediaInfo& rhs)
{
    this->_title = rhs._title;
    this->_videoId = rhs._videoId;
    this->_channelTitle = rhs._channelTitle;
    this->_description = rhs._description;
    return *this;
}

QSize MediaInfo::sizeHint() const
{
    return 50 * QSize(1, 1);
}

void MediaInfo::paint(QPainter *painter, const QRect &rect,
               const QPalette &palette) const
{
    Q_UNUSED(palette);

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    //painter->drawImage(rect, thumbnail);
    painter->drawText(rect, Qt::AlignCenter, _title);
    painter->restore();
}

void MediaInfo::loadImage(QUrl url) {
    QNetworkAccessManager manager(this);
    QNetworkRequest request(url);
    QByteArray bitstream = manager.get(request)->readAll();
    qDebug() << url;
    thumbnail = QImage::fromData(bitstream);
}
