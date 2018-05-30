#include "youtubesearch.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

YoutubeSearch::YoutubeSearch(const QString &query, const QString &API_KEY, QObject *parent)
    :QObject(parent), mCurl(curl_easy_init()), _query(query), API_KEY(API_KEY)
{
    curl_easy_setopt(mCurl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, &_response);
    curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, YoutubeSearch::write_res_data);
}

QList<MediaInfo> YoutubeSearch::search(size_t count)
{
    QString url;
    url.sprintf("%s?&key=%s&q=%s&maxResults=%lu&type=video&part=snippet",
                                   this->YOUTUBE_API, qPrintable(this->API_KEY), qPrintable(this->_query), count);
    qDebug() << url;
    curl_easy_setopt(mCurl, CURLOPT_URL, url.toUtf8().data());
    CURLcode res = curl_easy_perform(mCurl);
    if(res != CURLE_OK) {
        qFatal("%s", curl_easy_strerror(res));
    }
    QJsonDocument json_doc = QJsonDocument::fromJson(_response.toUtf8().data());
    QList<MediaInfo> items;
    for(QJsonValueRef item : json_doc.object().value("items").toArray())
        items.append(MediaInfo(item.toObject()));
    return items;
}

size_t YoutubeSearch::write_res_data(void *ptr, size_t size, size_t nmemb, QString *str)
{
    size_t len = size * nmemb;
    str->append(QString::fromUtf8(reinterpret_cast<char*>(ptr), len));
    return len;
}

YoutubeSearch::~YoutubeSearch()
{
    if (mCurl) {
        curl_easy_cleanup(mCurl);
    }
}
