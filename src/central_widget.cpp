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


    CentralWidget::CentralWidget(const QString& config_file_path, QWidget *parent)
        : QWidget(parent), m_ConfigFilePath(config_file_path)
    {

        const TcpConfig conf = [&config_file_path]()-> TcpConfig
        {
            const auto confDoc = YAML::LoadFile(config_file_path.toStdString());

            const auto tcpServerHostname = confDoc["tcp_server_hostname"].as<std::string>();
            const auto tcpServerPort = confDoc["tcp_server_port"].as<uint16_t>();
            const auto mainServerHostname = confDoc["main_server_hostname"].as<std::string>();
            const auto mainServerPort = confDoc["main_server_port"].as<uint16_t>();

            return {
                QString::fromStdString(tcpServerHostname),
                (quint16)tcpServerPort,
                QString::fromStdString(mainServerHostname),
                (quint16)mainServerPort
            };
        }();

        const AppConfig appConf = [&config_file_path]() -> AppConfig
        {
            const auto confDoc = YAML::LoadFile(config_file_path.toStdString());

            const auto username = confDoc["username"].as<std::string>();
            const auto email = confDoc["email"].as<std::string>();

            return {
                QString::fromStdString(username),
                QString::fromStdString(email)
            };
        }();

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
        m_ProfileWidget = new ProfileWidget({appConf.username, appConf.email});

        /* m_Client = new Client(m_ProfileWidget->getUserID(), "localhost", "3001", this); */
        m_Client = new Client(conf, m_ProfileWidget->getUserID(), this);
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

        connect(
            m_ContactsWidget,
            &ContactsWidget::addContactToDB,
            m_DatabaseHelper,
            &DatabaseHelper::onAddNewContactToDB
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
