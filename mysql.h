#ifndef MYSQL_H
#define MYSQL_H

#include <QtSql>
#include <QVector>

class MySQL
{
public:
    MySQL();
    QVector<QVector<QVariant>> Query( QString sql , QVector<QVariant> obj = QVector<QVariant>() );

private:
    QSqlDatabase DB;
};

class SQLException
{
public:
    SQLException(QString m = ""):message(m){}
    QString message;
};

#endif // MYSQL_H
