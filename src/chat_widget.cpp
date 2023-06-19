/**
 * @file chat_widget.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "messaging_application/chat_widget.hpp"

#include <QDebug>

namespace ma
{
    ChatWidget::ChatWidget(QWidget* parent)
        : QTabWidget(parent)
    {

        m_ChatTabs = std::unordered_map<std::string, ChatTab*>();

    }

    ChatWidget::~ChatWidget()
    {
        for(const auto& ct : m_ChatTabs)
        {
            delete ct.second;
        }
    }
    int ChatWidget::addChatTab(const QString& chat_name)
    {   

        if(m_ChatTabs.find(chat_name.toStdString()) != m_ChatTabs.end())
        {
            return -1;
        }
        ChatTab* newTab = new ChatTab(chat_name);
        m_ChatTabs[chat_name.toStdString()] = newTab;
        connect(
            newTab,
            &ChatTab::transferMessage,
            this,
            &ChatWidget::onMessageTransfered
        );
        
        // Add the new tab to the ChatWidget.
        this->addTab(m_ChatTabs.at(chat_name.toStdString()), chat_name);
        
        return 1;
    }

    void ChatWidget::onMessageTransfered(const QString& message, const QString& receiver)
    {
        MessageInfo mi;
        mi.message = message;
        mi.receiver = receiver;
        mi.sender = m_ChatOwnerID;
        emit sendMessage(mi);
        emit saveMessage(mi);
    }

    void ChatWidget::onNewMessageArrived(const MessageInfo& message_info)
    {
        m_ChatTabs.at(message_info.sender.toStdString())->insertNewMessage(message_info);
        emit saveMessage(message_info);
    }

    void ChatWidget::loadChatHistories(const QVector<ChatHistory>& histories)
    {
        const QString username = m_ChatOwnerID;
        
        for(const auto& hist : histories)
        {
            QString targetChatName  = [&hist, &username]() -> QString {
                QString target;
                bool flag = true;

                int c = 0;
                while(flag && c < hist.messages.size())
                {
                    /* qDebug() << "First" << hist.messages.at(c).first << "Second: " << hist.messages.at(c).second; */
                    if(hist.messages.at(c).first == username)
                    {   
                        c+=1;
                        continue;
                    }
                    else{
                        target = hist.messages.at(c).first;
                        break;
                    }
                    
                    c += 1;
                }

                /* for(const auto m : hist.messages)
                    qDebug() << m.first; */

                return target;
            }();

            m_ChatTabs.at(targetChatName.toStdString())->loadChatHistory(
                hist
            );
        }
        
    }

    /*
    -----------------------------------------
    -----------------------------------------
    -----------------------------------------
    */

    ChatTab::ChatTab(const QString& chat_tab_name, QWidget *parent)
        : QWidget(parent), m_ChatTabName(chat_tab_name)
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

        connect(
            m_SendMsgBtn,
            &QPushButton::clicked,
            this,
            &ChatTab::sendMessage
        );

    }

    void ChatTab::insertNewMessage(const MessageInfo& message_info)
    {
        QLabel* newMsgBox = new QLabel();
        newMsgBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        newMsgBox->setWordWrap(true);
        newMsgBox->setText(message_info.message);
        newMsgBox->setFrameStyle(QFrame::Box);

        m_MessageLayout->addWidget(newMsgBox, currRow, 0);

        currRow += 1;
    }

    void ChatTab::sendMessage()
    {
        const QString msgToSend = m_TypeMsgBox->toPlainText();

        QLabel* newMsgBox = new QLabel();
        newMsgBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        newMsgBox->setText(msgToSend);
        newMsgBox->setWordWrap(true);
        newMsgBox->setFrameStyle(QFrame::Box);

        m_MessageLayout->addWidget(newMsgBox, currRow, 1);
    
        m_TypeMsgBox->clear();

        currRow += 1;

        emit transferMessage(msgToSend, m_ChatTabName);
    }

    ChatTab::~ChatTab()
    {

    }

    void ChatTab::loadChatHistory(const ChatHistory& chat_history)
    {
        const QString receiverName = m_ChatTabName;
        for(std::size_t i = 0; i < chat_history.messages.size(); i++)
        {   
            /* qDebug() << chat_history.messages.at(i).first;  */
            const int col = [&chat_history, &receiverName, &i]() -> int {

                   
                if(chat_history.messages.at(i).first == receiverName)
                {
                    return 1;
                }

                return 0;

            }();

            QLabel* newMsgBox = new QLabel();
            newMsgBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
            newMsgBox->setText(chat_history.messages.at(i).second);
            newMsgBox->setWordWrap(true);
            newMsgBox->setFrameStyle(QFrame::Box);

            m_MessageLayout->addWidget(newMsgBox, currRow, col);

            currRow += 1;

        }
    }



    GroupChatTab::GroupChatTab(const QString& chat_tab_name, QWidget* parent)
        : ChatTab(chat_tab_name, parent)
    {

    }
}