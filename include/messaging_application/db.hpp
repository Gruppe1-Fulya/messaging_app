/**
 * @file db.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef DB_HPP_
#define DB_HPP_

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QVector>
#include <QString>
#include <QVariant>

class DatabaseHelper
{
    public:

    DatabaseHelper(
        const QString& database_type,
        const QString& host_name,
        const QString& database_name,
        const QString& user_name,
        const QString& password        
    );
    ~DatabaseHelper();

    bool connectToDB();

    QVector<QString> getContacts();

    inline bool isConnectionOk()
    {
        return m_IsConnectionOk;
    }

    private:

    QSqlDatabase* m_Database;

    QString m_DatabaseType;
    QString m_Hostname;
    QString m_DatabaseName;
    QString m_Username;
    QString m_Password;

    bool m_IsConnectionOk = false;



};

#endif