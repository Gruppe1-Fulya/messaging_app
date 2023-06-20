/**
 * @file group_chat.hpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef GROUP_CHAT_WIDGET_HPP_
#define GROUP_CHAT_WIDGET_HPP_

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QPushButton>
#include <QTextEdit>
#include <QScrollArea>
#include <QDir>
#include <QDebug>
#include <QLabel>

#include "messaging_application/definitions.hpp"

namespace ma
{
    class GroupChatList : public QWidget
    {
        Q_OBJECT

        public:

        GroupChatList(
            const QString& username, 
            QWidget* parent = nullptr
        );

        signals:
        
        void createGroupChat(const GroupInfo& group_info);

        void addGroupToDB(const GroupInfo& group_info);

        void openGroupChat(const GroupInfo& group_info);

        void newGroupMessage(const GroupMessage& msg);

        public slots:

        void addGroupChatToList(const GroupInfo& group_info);
        
        void getGroupChatInfo();

        void loadGroupChats(
            const QVector<GroupInfo>& chats
        );

        void onNewGroupMessageArrived(const GroupMessage& msg);

        private:

        QListWidget* m_GroupChatsList;

        QPushButton* m_AddGroupChatBtn;

        QVBoxLayout* m_MainLayout;

        QVector<QString> m_RegisteredChats;

        QString m_Username;

    };

    class GroupChatWidget : public QWidget
    {
        Q_OBJECT

        public:

        GroupChatWidget(
            const QString&  group_name,
            const QString& username,
            QWidget* parent = nullptr
        );

        GroupChatWidget(
            const GroupInfo&  group_info,
            const QString& username,
            QWidget* parent = nullptr
        );

        void initialMember()
        {
            addUserToChat(m_GroupName, m_Username);
        }

        ~GroupChatWidget(){}

        void insertNewMessage(const GroupMessage& msg);

        signals:

        void addNewUserToGroupDB(const QString& group_name, const QString& userID);

        void requestContacts();

        void transferMessage(const GroupMessage& msg_info);

        public slots:

        void onAddMemberBtnClicked();

        private:

        QVBoxLayout* m_MainLayout;

        QTextEdit* m_ContactNameBox;

        QPushButton* m_AddContactBtn;

        QHBoxLayout* m_ContactLayout;

        QGridLayout* m_MessageLayout;

        QHBoxLayout* m_SendMsgBoxLayout;

        QFrame* m_SendMsgBox;

        QFrame* m_MsgsFrame;

        QScrollArea* m_MsgsScrollArea;

        QTextEdit* m_TypeMsgBox;

        QPushButton* m_SendMsgBtn;
        
        int currRow = 0;

        QString m_GroupName;

        QString m_Username;

        QVector<QString> m_GroupMembers;

        void addUserToChat(const QString& group_name, const QString& userID);

        void sendMessage();


    };
}


#endif // GROUP_CHAT_WIDGET_HPP