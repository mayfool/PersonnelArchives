/*功能说明
文件名称：AccessDB.h
作    者：马进
联系方式：
创建时间：2017.09.28
目    的：用于Access数据库操作
功能描述：实现Access数据库的基本操作，mdb文件
约束条件：该编码使用了C++11特性，因此编译平台必须支持C++11标准，使用QT mingw32编译器
*/

#ifndef ACCESSDB_H
#define ACCESSDB_H

#include <QMessageBox>
#include <QDebug>
#include <Qtsql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQueryModel>
class AccessDB
{
public:
    AccessDB();
    bool connectDB(const QString& DatabaseName,
                   const QString& DatabasePath="",
                   const QString& connectName="",
                   const QString& HostName = "",
                   const QString& UserName = "",
                   const QString& Password = ""
                   );
    bool queryDB(const QString &query);
    void newQuery();
    //bool insertData(const QString &insert);
    bool openDB();
    void closeDB();
    QSqlQuery* getQuery();
    QSqlDatabase getSqlDB();
public:

private:
    QSqlDatabase m_sqlDB;
    //QString idName;
    QSqlQuery *m_query;
    QString m_databasePath;
    QString m_connectName;
    QString m_hostName;
    QString m_userName;
    QString m_password;

};

#endif // ACCESSDB_H
