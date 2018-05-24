#ifndef YOUTUBESEARCH_H
#define YOUTUBESEARCH_H

#include <QObject>
#include <QList>
#include <curl/curl.h>
#include "mediainfo.h"

class YoutubeSearch : public QObject
{
    Q_OBJECT
public:
    explicit YoutubeSearch(const QString &query, const QString& API_KEY, QObject *parent = nullptr);
    QList<MediaInfo> search(size_t count);
    ~YoutubeSearch();
signals:

public slots:

private:
    static size_t write_res_data(void *ptr, size_t size, size_t nmemb, QString *str);
    CURL* mCurl;
    QString _response;
    const QString _query;
    const QString API_KEY;
    const char* YOUTUBE_API = "https://www.googleapis.com/youtube/v3/search";
};

#endif // YOUTUBESEARCH_H
