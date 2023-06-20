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

        emit addGroupToDB(group_info);
        emit openGroupChat(group_info);

    }

    void GroupChatList::loadGroupChats(const QVector<GroupInfo>& chats)
    {
        for(const auto& g : chats)
        {
            m_GroupChatsList->addItem(
                new QListWidgetItem(g.groupName)
            );
            m_RegisteredChats.push_back(g.groupName);
            emit openGroupChat(g);
        }

    }

    void GroupChatList::onNewGroupMessageArrived(const GroupMessage& msg)
    {
        const auto isChatRegistered = std::find(
            m_RegisteredChats.begin(),
            m_RegisteredChats.end(),
            msg.groupName
        );

        if(isChatRegistered == m_RegisteredChats.end())
        {
            m_GroupChatsList->addItem(new QListWidgetItem(msg.groupName));
            m_RegisteredChats.push_back(msg.groupName);
            
            GroupInfo gi;
            gi.groupName = msg.groupName;
            gi.members = msg.members;
            const int updateMember = [&gi, this]() -> int{
                for(std::size_t i = 0; i < gi.members.size(); i++)
                {
                    if(gi.members.at(i) == this->m_Username)
                    {
                        return i;
                    }
                }

                return -1;
            }();
            if(updateMember != -1)
                gi.members.replace(updateMember, msg.sender);

            emit addGroupToDB(gi);
            emit openGroupChat(gi);

            emit newGroupMessage(msg);
            /* qDebug() << msg.data; */

        }
        else
        {
            GroupInfo gi;
            gi.groupName = msg.groupName;
            gi.members = msg.members;
            const int updateMember = [&gi, this]() -> int{
                for(std::size_t i = 0; i < gi.members.size(); i++)
                {
                    if(gi.members.at(i) == this->m_Username)
                    {
                        return i;
                    }
                }

                return -1;
            }();

            if(updateMember != -1)
                gi.members.replace(updateMember, msg.sender);

            emit newGroupMessage(msg);
            /* qDebug() << msg.data; */
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

        m_ContactLayout = new QHBoxLayout();
        m_ContactNameBox = new QTextEdit();
        m_ContactNameBox->setFixedHeight(30);
        m_AddContactBtn = new QPushButton("Add Member");
        m_ContactLayout->addWidget(m_ContactNameBox, 50);
        m_ContactLayout->addWidget(m_AddContactBtn, 50);

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
        m_MainLayout->addLayout(m_ContactLayout, 5);
        m_MainLayout->addWidget(m_MsgsScrollArea, 90);
        m_MainLayout->addWidget(m_SendMsgBox, 5);

        connect(
            m_AddContactBtn,
            &QPushButton::clicked,
            this,
            &GroupChatWidget::onAddMemberBtnClicked
        );
        
        connect(
            m_SendMsgBtn,
            &QPushButton::clicked,
            this,
            &GroupChatWidget::sendMessage
        );

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

    void GroupChatWidget::onAddMemberBtnClicked()
    {
        addUserToChat(
            m_GroupName,
            m_ContactNameBox->toPlainText()
        );

        m_ContactNameBox->clear();
    }
    
    void GroupChatWidget::sendMessage()
    {
        GroupMessage gm;
        const QString msgToSend = m_TypeMsgBox->toPlainText();

        QLabel* newMsgBox = new QLabel();
        newMsgBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        newMsgBox->setText(msgToSend);
        newMsgBox->setWordWrap(true);
        newMsgBox->setFrameStyle(QFrame::Box);

        QLabel* userBox = new QLabel();
        userBox->setText(m_Username);
        userBox->setAlignment(Qt::AlignTop);
        userBox->setFixedSize(255, 20);
        
        QVBoxLayout* msgLayout = new QVBoxLayout();
        msgLayout->setStretch(0, 0);
        msgLayout->setSpacing(0);
        msgLayout->setContentsMargins(0, 0, 0, 0);
        msgLayout->addWidget(userBox, 0);
        msgLayout->addWidget(newMsgBox, 0);
            

        m_MessageLayout->addLayout(msgLayout, currRow, 1);
        m_MessageLayout->setSpacing(0);
        m_TypeMsgBox->clear();

        currRow += 1;

        gm.groupName = m_GroupName;
        const QVector<QString> memberList = [this]() -> QVector<QString>{
            QVector<QString> members;
            for(const auto& member : this->m_GroupMembers)
            {
                    
                if(member != this->m_Username)
                {
                    members.push_back(member);
                }
            }

            return members;
        }();

        gm.members = memberList;
        gm.sender = m_Username;
        gm.data = msgToSend;

        emit transferMessage(gm);
    }

    void GroupChatWidget::insertNewMessage(const GroupMessage& msg)
    {
        QLabel* newMsgBox = new QLabel();
        newMsgBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        newMsgBox->setWordWrap(true);
        newMsgBox->setText(msg.data);
        newMsgBox->setFrameStyle(QFrame::Box);

        QLabel* userBox = new QLabel();
        userBox->setText(msg.sender);
        userBox->setAlignment(Qt::AlignTop);
        userBox->setFixedSize(255, 20);
        
        QVBoxLayout* msgLayout = new QVBoxLayout();
        msgLayout->setStretch(0, 0);
        msgLayout->setSpacing(0);
        msgLayout->setContentsMargins(0, 0, 0, 0);
        msgLayout->addWidget(userBox, 0);
        msgLayout->addWidget(newMsgBox, 0);

        m_MessageLayout->addLayout(msgLayout, currRow, 0);
        m_MessageLayout->setSpacing(0);

        currRow += 1;
    }

}