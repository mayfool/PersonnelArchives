#include "mysqldb.h"



MysqlDB::MysqlDB()
{
    m_databasePath = "";
    m_connectName  = "";
    m_hostName     = "";
    m_userName     = "";
    m_password     = "";
}
bool MysqlDB::connectDB(const QString& DatabasePath,
                         const QString& ConnectName,
                         const QString& HostName,
                         const QString& UserName,
                         const QString& Password)
{
    try
    {
        //const QString connID(ConnectName);
        const QString m_databasePath(DatabasePath);
        const QString m_connectName(ConnectName);
        const QString m_hostName(HostName);
        const QString m_userName(UserName);
        const QString m_password(Password);

        m_sqlDB = QSqlDatabase::database(m_connectName,false);

        if(m_sqlDB.isValid())//存在连接直接返回
        {
            if(m_sqlDB.isOpen())
                return true;
        }
        else
        {
            m_sqlDB = QSqlDatabase::addDatabase("QMYSQL");



                m_sqlDB.setHostName("localhost");
                m_sqlDB.setPort(3306);
                m_sqlDB.setDatabaseName("manager");
                m_sqlDB.setUserName("root");
                m_sqlDB.setPassword("hd951113");
            if (!db.open()) {
                QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                    QObject::tr("Unable to establish a database connection.\n"
                                "This example needs SQLite support. Please read "
                                "the Qt SQL driver documentation for information how "
                                "to build it.\n\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
                return false;
            }
            //connection.setUserName(UserName);
            //connection.setPassword(Password);
            if(!m_sqlDB.open())
            {
                QMessageBox::critical(0,QObject::tr("打开数据库失败！"),m_sqlDB.lastError().text());
                return false;
            }
            else
            {
                newQuery();
                qDebug()<<"数据库打开成功！";
                return true;
            }
        }
    }
    catch(...)
    {
        qDebug()<<"MysqlDB::connectDB函数异常！";
    }
}

void MysqlDB::newQuery()
{
    m_query = new QSqlQuery(m_sqlDB);
}

bool MysqlDB::queryDB(const QString &query)
{
    if(!m_query->prepare(query))//如果加载失败，刚断开连接，然后再连接
    {
        m_sqlDB.close();
        if(!openDB())
        {
            return false;
        }
        qDebug()<<"new.....Connect";
    }

    return(m_query->exec());
}

bool MysqlDB::openDB()
{
    //idName = connectName;
    if(!connectDB(m_databasePath,m_connectName,m_hostName,m_userName,m_password))
    {
        QMessageBox msgBox;
        msgBox.setText("数据库连接失败");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return false;
    }
    return true;
}

void MysqlDB::closeDB()
{
    //const QString connID(idName);
    //connection = QSqlDatabase::database(connID,false);
    m_sqlDB.close();
    m_sqlDB.removeDatabase(m_connectName);
}
QSqlQuery* MysqlDB::getQuery()
{
    return m_query;
}
QSqlDatabase MysqlDB::getSqlDB()
{
    return m_sqlDB;
}
