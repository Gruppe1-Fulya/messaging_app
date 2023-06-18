/**
 * @file central_widget.cpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "messaging_application/central_widget.hpp"
#include <QDebug>

namespace ma
{

    CentralWidget::CentralWidget(QWidget *parent)
    {

        m_DatabaseHelper = new DatabaseHelper(
            "QMYSQL",
            "localhost",
            "msgapp_db",
            "admin",
            "123456"
        );
        

        if(m_DatabaseHelper->connectToDB())
            qDebug() << "Connected to the database";
        

        m_MainLayout = new QHBoxLayout(this);

        m_ProfileAndContactsLayout = new QVBoxLayout();

        m_ContactsWidget = new ContactsWidget();
        if(m_DatabaseHelper->isConnectionOk())
        {
            QVector<QString> contactsFromDB;

            contactsFromDB = m_DatabaseHelper->getContacts();
            if(contactsFromDB.size() != 0)
                m_ContactsWidget->loadContacts(contactsFromDB);  
            else
                qDebug() << "No contacts found";

        }

        
        m_ChatWidget = new ChatWidget();
        m_ProfileWidget = new ProfileWidget({"Eren Naci Odabasi", "enaciodabasi@outlook.com"});

        m_Client = new Client(m_ProfileWidget->getUserID(), "localhost", "3001", this);
        m_ChatWidget->setChatOwnerID(m_ProfileWidget->getUserID());

        m_ProfileAndContactsLayout->addWidget(m_ProfileWidget, 20);
        m_ProfileAndContactsLayout->addWidget(m_ContactsWidget, 80);
        //m_MainLayout->addWidget(m_ContactsWidget, 35);
        m_MainLayout->addLayout(m_ProfileAndContactsLayout, 35);
        m_MainLayout->addWidget(m_ChatWidget, 65);
        
        this->setLayout(m_MainLayout);

        connect(
            m_ContactsWidget,
            &ContactsWidget::openChat,
            m_ChatWidget,
            &ChatWidget::addChatTab  
        );

        connect(
            m_ChatWidget,
            &ChatWidget::sendMessage,
            m_Client,
            &Client::onSendMessage
        );

        connect(
            m_Client,
            &Client::newMessageArrived,
            m_ChatWidget,
            &ChatWidget::onNewMessageArrived
        );

        

    }

    CentralWidget::~CentralWidget()
    {
        delete m_DatabaseHelper;
    }

    void CentralWidget::createUI()
    {
        
    }

}
