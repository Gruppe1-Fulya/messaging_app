/**
 * @file chat_widget.hpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CHAT_WIDGET_HPP
#define CHAT_WIDGET_HPP

#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QFrame>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QString>
#include <QLabel>
#include <QTextEdit>
#include <QPainter>

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

#include "messaging_application/definitions.hpp"
#include "messaging_application/group_chat_widget.hpp"

namespace ma
{

    class ChatTab;
    
    class ChatWidget : public QTabWidget
    {

        Q_OBJECT

        public:

        ChatWidget(QWidget* parent = nullptr);
        ~ChatWidget();

        int addChatTab(const QString& chat_name);

        void addGroupChatTab(const GroupInfo& group_info);

        void setChatOwnerID(const QString& chat_owner_id)
        {
            m_ChatOwnerID = chat_owner_id;
        }

        void loadChatHistories(const QVector<ChatHistory>& histories);

        signals:

        void sendMessage(const MessageInfo& message_info);

        void sendGroupMessage(const GroupMessage& msg);

        void saveMessage(const MessageInfo& message_info);

        void addMemberToDB(const QString& group_name, const QString& userID);

        public slots:

        void onMessageTransfered(const QString& message, const QString& receiver);

        void onGroupMessageTransfered(const GroupMessage& msg);

        void onNewMessageArrived(const MessageInfo& message_info);

        void onNewGroupMessageArrived(const GroupMessage& msg);

        void onAddMemberToDB(
            const QString& group_name,
            const QString& userID
        );

        private:

        QString m_ChatOwnerID;

        std::unordered_map<std::string, ChatTab*> m_ChatTabs;   

        std::unordered_map<std::string, GroupChatWidget*> m_GroupChatTabs;

        QVector<QString> m_Contacts;      

    };

    /*
    -----------------------------------------
    -----------------------------------------
    -----------------------------------------
    */

    class ChatTab : public QWidget
    {
        Q_OBJECT

        public:

        ChatTab(
            const QString& chat_tab_name, 
            const QString& chat_owner_name,
            QWidget* parent = nullptr
        );
        ~ChatTab();

        inline const QString getTabName() const
        {
            return m_ChatTabName;
        }

        void insertNewMessage(const MessageInfo& message_info);

        void loadChatHistory(const ChatHistory& chat_history);
        
        signals:

        void transferMessage(const QString& message, const QString& receiver);

        public slots:
        
    
        private:

        QVBoxLayout* m_MainLayout;

        QGridLayout* m_MessageLayout;

        QHBoxLayout* m_SendMsgBoxLayout;

        QFrame* m_SendMsgBox;

        QFrame* m_MsgsFrame;

        QScrollArea* m_MsgsScrollArea;

        QTextEdit* m_TypeMsgBox;

        QPushButton* m_SendMsgBtn;
        
        int currRow = 0;

        QString m_ChatTabName;

        QString m_ChatOwnerName;

        void sendMessage();
        

    };


} // End of namespace ma

#endif // CHAT_WIDGET_HPP