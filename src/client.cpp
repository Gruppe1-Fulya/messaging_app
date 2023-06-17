/**
 * @file client.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "messaging_application/client.hpp"

Client::Client(QObject* parent)
    : QObject(parent)
{
    m_ListenerServer = new QTcpServer(this);

    QObject::connect(m_ListenerServer, &QTcpServer::newConnection, this, &Client::newConnection);

    if(!m_ListenerServer->listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Can not start server";
    }

}

Client::~Client()
{
    

    
}

void Client::newConnection()
{
    QTcpSocket* socket = m_ListenerServer->nextPendingConnection();
    
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(
        socket->readAll(),
        &parseError
    );

    if(parseError.error != QJsonParseError::NoError)
    {
        return;
    }

    for(const QString& key : jsonDoc.object().keys())
    {
        qDebug() << jsonDoc.object()[key];
    }
    
}

bool Client::connect()
{
    m_Socket = new QTcpSocket(this);

    m_Socket->connectToHost(
        m_HostName,
        m_PortNum
    );

    if(!m_Socket->waitForConnected(5000))
    {   

        return false;
    }

    return true;
}