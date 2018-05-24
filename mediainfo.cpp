#include "mediainfo.h"

MediaInfo::MediaInfo(const QJsonObject& jObj, QObject *parent) : QObject(parent)
{
    QJsonObject snippet = jObj["snippet"].toObject();
    _videoId = jObj["id"].toObject()["videoId"].toString();
    _title = snippet["title"].toString();
    _description = snippet["description"].toString();
    _channelTitle = snippet["channelTitle"].toString();
}

MediaInfo::MediaInfo(const MediaInfo &mediaInfo, QObject *parent)
    : QObject(parent), _title(mediaInfo._title), _videoId(mediaInfo._videoId), _channelTitle(mediaInfo._channelTitle), _description(mediaInfo._description)
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
