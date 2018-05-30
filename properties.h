#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QMap>
#include <QQueue>

struct Properties
{
    QString account;
    QString room;
    QString music;
    QString musicID;
    QQueue<int> beats;
    QMap<QString,QMap<int,int>> hits;
    QMap<QString,QMap<int,int>>scores;
};

#endif // PROPERTIES_H
