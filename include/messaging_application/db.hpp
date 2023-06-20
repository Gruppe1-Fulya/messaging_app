/**
 * @file db.hpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
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
#include <QDebug>

#include <optional>

#include "messaging_application/definitions.hpp"

class DatabaseHelper : public QObject
{
    Q_OBJECT

    public:

    DatabaseHelper(
        const QString& database_type,
        const QString& host_name,
        const QString& database_name,
        const QString& user_name,
        const QString& password,
        QObject* parent = nullptr        
    );
    ~DatabaseHelper();

    bool connectToDB();

    QVector<QString> getContacts();

    QVector<GroupInfo> getGroupChats();

    std::optional<ChatHistory> getChatHistory(
        const QString& user,
        const QString& from
    );

    void createTableForUser(const QString& id);

    inline bool isConnectionOk()
    {
        return m_IsConnectionOk;
    }

    public slots:

    void onSaveChatToDB(const MessageInfo& message_info);

    void onAddNewContactToDB(const QString& contact_id);

    void onAddGroupToDB(const GroupInfo& group_info);

    void onAddMemberToDB(const QString& group_name, const QString& userID);

    private:

    QSqlDatabase* m_Database;

    QString m_DatabaseType;
    QString m_Hostname;
    QString m_DatabaseName;
    QString m_Username;
    QString m_Password;

    QString m_UserID;
    QString m_UserContactsTableName;
    QString m_UserChatHistoryTableName;

    bool m_IsConnectionOk = false;

};

#endif