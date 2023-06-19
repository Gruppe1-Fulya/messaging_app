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
    query.exec("SELECT * FROM " + m_UserContactsTableName);

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
    
    query.prepare("SELECT email FROM " + m_UserContactsTableName + " WHERE email=:id");
    query.bindValue(":id", contact_id);
    query.exec();
    if(query.size() > 0)
    {
        return;
    }

    query.clear();
    query.prepare("INSERT INTO " + m_UserContactsTableName + "(email) VALUES(:email)");
    /* query.bindValue(":name", contact_id); */
    query.bindValue(":email", contact_id);

    query.exec();

}


void DatabaseHelper::onSaveChatToDB(const MessageInfo& message_info)
{
    
    QSqlQuery q;
    q.prepare("INSERT INTO " + m_UserChatHistoryTableName + "(owner, message) VALUES(:owner, :message)");
    q.bindValue(":owner", message_info.sender);
    q.bindValue(":message", message_info.message);
    
    q.exec();

}

std::optional<ChatHistory> DatabaseHelper::getChatHistory(
    const QString& user,
    const QString& from
)
{

    QSqlQuery q;

    q.prepare(
        "SELECT * FROM " + m_UserChatHistoryTableName + " WHERE owner=:owner1 OR owner=:owner2"
    );
    q.bindValue(":owner1", user);
    q.bindValue(":owner2", from);
    q.exec();

    if(q.size() > 0)
    {   

        ChatHistory ch;

        /* while(q.next())
        {
            if(from == q.value("owner").toString())
            {
                ch.otherMsgs.push_back(q.value("message").toString());
            }
            else
            {
                ch.userMsgs.push_back(q.value("message").toString());
            }
        } */

        while(q.next())
        {
            ch.messages.push_back(qMakePair(
                q.value("owner").toString(),
                q.value("message").toString()
            ));
        }

        return ch;
    }

    return std::nullopt;
}

void DatabaseHelper::createTableForUser(const QString& id)
{
    const auto tableName = id.split("@").first();

    QSqlQuery q;

    QString statement = 
    "CREATE TABLE if not exists msgapp_db." + 
    tableName + 
    "_contacts(id int auto_increment, email varchar(255) not null, primary key(id, email));";

    q.exec(statement);

    q.clear();

    statement = 
    "CREATE TABLE if not exists msgapp_db." + 
    tableName + 
    "_chat_history(id int auto_increment, owner varchar(255) not null, message varchar(500), primary key(id, owner));";
    q.exec(statement);

    m_UserContactsTableName = tableName + "_contacts";
    m_UserChatHistoryTableName = tableName + "_chat_history";

}