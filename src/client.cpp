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
    QHostAddress hostAddr("localhost");

    if(!m_ListenerServer->listen(hostAddr, 3001))
    {
        qDebug() << "Can not start server";
    }

}

Client::~Client()
{
    
    m_ListenerServer->deleteLater();
    
}

void Client::onSendMessage(const MessageInfo& message_info)
{

    QTcpSocket* socket = new QTcpSocket(this);
    socket->connectToHost(
        "localhost",
        3000
    );
    if(!socket->waitForConnected(5000))
        return;

    //const char* msg = message_info.message.toStdString().c_str();

    const auto dataJObj = QJsonObject{{"data", message_info.message}};
    const auto rJObj = QJsonObject{{"receiver", message_info.receiver}};
    const auto sJObj = QJsonObject{{"sender", message_info.sender}};

    const auto jArr = QJsonArray{dataJObj, rJObj, sJObj};

    /* const auto msgObj = QJsonObject{{"message", jArr}}; */
    const auto msgObj = QJsonObject{
        {"data", message_info.message},
        {"receiver", message_info.receiver},
        {"sender", message_info.sender}
    };
    const auto msgJDoc = QJsonDocument{msgObj};    
    
    /* qDebug() << qPrintable(QString::fromUtf8(msgJDoc.toJson()));
 */
    socket->write(msgJDoc.toJson());
    //socket->write(msg, sizeof(msg));
    //socket->waitForBytesWritten();
    
    socket->close();
}

void Client::readyRead()
{
    QJsonParseError parseError;
    const auto incoming = m_Socket->readAll();
    
    QJsonDocument jsonDoc = QJsonDocument::fromJson(
        incoming,
        &parseError
    );
    
    if(parseError.error != QJsonParseError::NoError)
    {
        qDebug() << parseError.errorString();
        return;
    }

    /* QJsonArray jsonArr = jsonDoc.array();

    if(jsonArr.empty())
    {   
        qDebug() << "JSON array is empty";
        return;
    } */
    
    /* const auto msgJson = jsonArr.first().toObject(); */
    const auto msgJson = jsonDoc.object();
    
    const auto msg = msgJson.value("data").toString();
    const auto sender = msgJson.value("sender").toString();
    const auto receiver = msgJson.value("receiver").toString();
    
    MessageInfo mi = {msg, sender, receiver};

    emit newMessageArrived(mi);
}
void Client::disconnected()
{
    m_Socket->deleteLater();
}

void Client::newConnection()
{
   
    m_Socket = new QTcpSocket();
    m_Socket = m_ListenerServer->nextPendingConnection();
    connect(m_Socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    connect(m_Socket, &QTcpSocket::disconnected, this, &Client::disconnected);

}
