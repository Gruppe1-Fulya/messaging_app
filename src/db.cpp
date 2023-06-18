/**
 * @file db.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "messaging_application/db.hpp"

DatabaseHelper::DatabaseHelper(
    const QString& database_type,
    const QString& host_name,
    const QString& database_name,
    const QString& user_name,
    const QString& password,
    QObject* parent
) : QObject(parent),
    m_DatabaseType(database_type),
    m_Hostname(host_name),
    m_DatabaseName(database_name),
    m_Username(user_name),
    m_Password(password)
{
    m_Database = new QSqlDatabase(
        QSqlDatabase::addDatabase(m_DatabaseType)
    );

    m_Database->setHostName(m_Hostname);
    m_Database->setDatabaseName(m_DatabaseName);
    m_Database->setUserName(m_Username);
    m_Database->setPassword(m_Password);

}

DatabaseHelper::~DatabaseHelper()
{
    m_Database->close();
    delete m_Database;
}
bool DatabaseHelper::connectToDB()
{

    bool conn = false;
    if(m_Database)
    {
        conn = m_Database->open();
    }
    
    m_IsConnectionOk = conn;

    return conn;
}

QVector<QString> DatabaseHelper::getContacts()
{
    QVector<QString> c;

    QSqlQuery query;
    query.exec("SELECT * FROM contacts");

    if(query.size() > 0)
    {
        while(query.next())
        {   
            QString currName = query.value("email").toString().toUtf8().constData();
            c.push_back(currName);
        }
    }

    return c;
}

void DatabaseHelper::onAddNewContactToDB(const QString& contact_id)
{
    /* qDebug() << contact_id; */
    QSqlQuery query;
    
    query.prepare("SELECT email FROM contacts WHERE email=:id");
    query.bindValue(":id", contact_id);
    query.exec();
    if(query.size() > 0)
    {
        return;
    }

    query.clear();
    query.prepare("INSERT INTO contacts (name, email) VALUES(:name,:email)");
    query.bindValue(":name", contact_id);
    query.bindValue(":email", contact_id);

    query.exec();

}