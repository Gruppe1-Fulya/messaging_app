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

#include "chat_widget.hpp"

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
        // Check if the ChatTab container has a tab with the given name.
        //if(m_ChatTabs.find(chat_name) == m_ChatTabs.end())
        //{
        //    return 0; // If a chat with that name already exists return -1;
        //}
        // Create a tab with the given name.
        m_ChatTabs[chat_name.toStdString()] = new ChatTab(chat_name);
        
        // Add the new tab to the ChatWidget.
        this->addTab(m_ChatTabs.at(chat_name.toStdString()), chat_name);
        
        return 1;
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

    void ChatTab::messageReceived(const QString& sender_name, const QString& message)
    {
        QLabel* newMsgBox = new QLabel();
        newMsgBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        newMsgBox->setWordWrap(true);
        newMsgBox->setText(message);
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
    }

    ChatTab::~ChatTab()
    {

    }

    GroupChatTab::GroupChatTab(const QString& chat_tab_name, QWidget* parent)
        : ChatTab(chat_tab_name, parent)
    {

    }
}