#include "mysql.h"
#include <QMessageBox>

MySQL::MySQL()
{
    DB = QSqlDatabase::database();
    if(DB.isValid()) return;
    DB = QSqlDatabase::addDatabase("QMYSQL");
    DB.setHostName("mysyu.ddns.net");
    DB.setUserName("jbit");
    DB.setPassword("jbit");
    DB.setDatabaseName("jbit");
    DB.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=2");
}

QVector<QVector<QVariant>> MySQL::Query( QString sql , QVector<QVariant> obj  )
{
    if( !DB.open() ) throw SQLException(DB.lastError().text());
    QSqlQuery query;
    query.prepare(sql);
    for( int i = 0 ; i < obj.size() ; i++ )
    {
        query.addBindValue(obj[i]);
    }
    if(!query.exec())
        throw SQLException(query.lastError().text());
    QVector<QVector<QVariant>> result;
    while(query.next())
    {
        QVector<QVariant> row;
        for(int i = 0 ; i < query.record().count() ; i++)
        {
            row.push_back(query.value(i));
        }
        result.push_back(row);
    }
    DB.close();
    return result;
}
