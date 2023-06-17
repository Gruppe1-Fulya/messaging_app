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

    const auto msgObj = QJsonObject{{"message", jArr}};
    const auto msgJDoc = QJsonDocument{msgObj};    
    
    qDebug() << qPrintable(QString::fromUtf8(msgJDoc.toJson()));

    socket->write(msgJDoc.toJson());
    //socket->write(msg, sizeof(msg));
    //socket->waitForBytesWritten();

    socket->close();
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

    QJsonArray jsonArr = jsonDoc.array();

    if(jsonArr.empty())
    {
        return;
    }

    const auto msgJson = jsonArr.first().toObject();
    
    const auto msg = msgJson.value("message").toString();
    const auto sender = msgJson.value("sender").toString();
    const auto receiver = msgJson.value("receiver").toString();

    MessageInfo mi = {msg, sender, receiver};

    emit newMessageArrived(mi);


}
