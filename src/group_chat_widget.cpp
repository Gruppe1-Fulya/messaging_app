/**
 * @file group_chat_widget.cpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "messaging_application/group_chat_widget.hpp"

namespace ma
{
    GroupChatList::GroupChatList(const QString& username, QWidget* parent)
        : QWidget(parent), m_Username(username)
    {

        m_MainLayout = new QVBoxLayout();

        m_AddGroupChatBtn = new QPushButton("Create Group");

        m_GroupChatsList = new QListWidget(this);
        m_MainLayout->addWidget(m_GroupChatsList, 90);
        m_MainLayout->addWidget(m_AddGroupChatBtn, 10);

        connect(
            m_AddGroupChatBtn,
            &QPushButton::clicked,
            this,
            &GroupChatList::getGroupChatInfo
        );

        connect(
            this,
            &GroupChatList::createGroupChat,
            this,
            &GroupChatList::addGroupChatToList
        );


        this->setLayout(m_MainLayout);
    }

    void GroupChatList::getGroupChatInfo()
    {
        bool ok;
        QString groupName = QInputDialog::getText(
            this,
            tr("Add Group"),
            tr("Group Name:"),
            QLineEdit::Normal,
            QDir::home().dirName(),
            &ok
        );

        if(ok && !groupName.isEmpty())
        {
            GroupInfo gi;
            gi.groupName = groupName;
            emit createGroupChat(gi);
        }
    }

    void GroupChatList::addGroupChatToList(const GroupInfo& group_info)
    {
        m_GroupChatsList->addItem(new QListWidgetItem(group_info.groupName));

        m_RegisteredChats.push_back(group_info.groupName);

        addGroupToDB(group_info);
        emit openGroupChat(group_info);

    }

    void GroupChatList::loadGroupChats(const QVector<GroupInfo>& chats)
    {
        for(const auto& g : chats)
        {
            m_GroupChatsList->addItem(
                new QListWidgetItem(g.groupName)
            );

            emit openGroupChat(g);
        }

    }

    GroupChatWidget::GroupChatWidget(
        const QString&  group_name,
        const QString& username,
        QWidget* parent
    )   : m_GroupName(group_name), m_Username(username)
    {
        m_MainLayout = new QVBoxLayout(this);

        m_MessageLayout = new QGridLayout();

        m_MsgsFrame = new QFrame();
        m_MsgsFrame->setMinimumHeight(500);
        m_MsgsFrame->setLayout(m_MessageLayout);

        m_MsgsScrollArea = new QScrollArea(this);
        m_MsgsScrollArea->setBackgroundRole(QPalette::Light);
        m_MsgsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_MsgsScrollArea->setWidgetResizable(true);

        m_SendMsgBoxLayout = new QHBoxLayout();
        m_SendMsgBox = new QFrame();

        m_TypeMsgBox = new QTextEdit();
        m_SendMsgBtn = new QPushButton("Send");

        m_SendMsgBoxLayout->addWidget(m_TypeMsgBox);
        m_SendMsgBoxLayout->addWidget(m_SendMsgBtn);
        m_SendMsgBox->setLayout(m_SendMsgBoxLayout);

        m_MsgsScrollArea->setWidget(m_MsgsFrame);
        m_MainLayout->addWidget(m_MsgsScrollArea, 90);
        m_MainLayout->addWidget(m_SendMsgBox, 10);

        this->setLayout(m_MainLayout);
    }

    GroupChatWidget::GroupChatWidget(
        const GroupInfo&  group_info,
        const QString& username,
        QWidget* parent
    )   : m_GroupName(group_info.groupName), m_GroupMembers(group_info.members), m_Username(username)
    {
        m_MainLayout = new QVBoxLayout(this);

        m_MessageLayout = new QGridLayout();

        m_MsgsFrame = new QFrame();
        m_MsgsFrame->setMinimumHeight(500);
        m_MsgsFrame->setLayout(m_MessageLayout);

        m_MsgsScrollArea = new QScrollArea(this);
        m_MsgsScrollArea->setBackgroundRole(QPalette::Light);
        m_MsgsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_MsgsScrollArea->setWidgetResizable(true);

        m_SendMsgBoxLayout = new QHBoxLayout();
        m_SendMsgBox = new QFrame();

        m_TypeMsgBox = new QTextEdit();
        m_SendMsgBtn = new QPushButton("Send");

        m_SendMsgBoxLayout->addWidget(m_TypeMsgBox);
        m_SendMsgBoxLayout->addWidget(m_SendMsgBtn);
        m_SendMsgBox->setLayout(m_SendMsgBoxLayout);

        m_MsgsScrollArea->setWidget(m_MsgsFrame);
        m_MainLayout->addWidget(m_MsgsScrollArea, 90);
        m_MainLayout->addWidget(m_SendMsgBox, 10);
        
        this->setLayout(m_MainLayout);
    }

    void GroupChatWidget::addUserToChat(const QString& group_name, const QString& userID)
    {
        const auto isUserPresent = qFind(
            m_GroupMembers.begin(),
            m_GroupMembers.end(),
            userID
        );

        if(isUserPresent == m_GroupMembers.end())
        {
            m_GroupMembers.push_back(userID);
            /* qDebug() << "Adding user" << userID; */
            emit addNewUserToGroupDB(m_GroupName, userID);
        }
    }

}