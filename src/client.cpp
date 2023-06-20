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

Client::Client(const QString& sender_id, const QString& address, const QString& port, QObject* parent)
    : QObject(parent), m_HostName(address), m_SenderID(sender_id)
{

    m_PortNum = port;

    m_ListenerServer = new QTcpServer(this);

    QObject::connect(m_ListenerServer, &QTcpServer::newConnection, this, &Client::newConnection);
    QHostAddress hostAddr("localhost");

    if(!m_ListenerServer->listen(hostAddr, 3001))
    {
        qDebug() << "Can not start server";
    }
    {
        QTcpSocket* initialConnSocket = new QTcpSocket();
        initialConnSocket->connectToHost(
            "localhost",
            3000
        );
        if(!initialConnSocket->waitForConnected(5000))
            return;
        const QString addr = m_HostName + ":" + m_PortNum;
        qDebug() << addr;
        const auto msgObj = QJsonObject{
            {"data", ""},
            {"receiver", ""},
            {"sender", m_SenderID},
            {"addr", addr},
            {"group", ""}
        };
        const auto msgJDoc = QJsonDocument{msgObj};    
    
        initialConnSocket->write(msgJDoc.toJson());

        initialConnSocket->waitForBytesWritten(3000);

        initialConnSocket->close();
    }

}

Client::Client(const TcpConfig& app_config, const QString sender_id, QObject* parent)
    : QObject(parent), m_AppConfig(app_config), m_SenderID(sender_id)
{

    const auto hostname = m_AppConfig.mainServerHostname;

    m_ListenerServer = new QTcpServer(this);

    QObject::connect(m_ListenerServer, &QTcpServer::newConnection, this, &Client::newConnection);
    QHostAddress hostAddr(hostname);

    if(!m_ListenerServer->listen(hostAddr, m_AppConfig.tcpServerPort))
    {
        qDebug() << "Can not start server";
    }
    {
        QTcpSocket* initialConnSocket = new QTcpSocket();
        initialConnSocket->connectToHost(
            m_AppConfig.mainServerHostname,
            m_AppConfig.mainServerPort
        );
        if(!initialConnSocket->waitForConnected(5000))
            return;
        const QString addr = m_AppConfig.tcpServerHostname + ":" + QString::number(m_AppConfig.tcpServerPort);
        const auto msgObj = QJsonObject{
            {"data", ""},
            {"receiver", ""},
            {"sender", m_SenderID},
            {"addr", addr},
            {"group", ""}
        };
        const auto msgJDoc = QJsonDocument{msgObj};    
    
        initialConnSocket->write(msgJDoc.toJson());

        initialConnSocket->waitForBytesWritten(3000);

        initialConnSocket->close();
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
        m_AppConfig.mainServerHostname,
        m_AppConfig.mainServerPort
    );
    if(!socket->waitForConnected(5000))
        return;

    //const char* msg = message_info.message.toStdString().c_str();

    const auto dataJObj = QJsonObject{{"data", message_info.message}};
    const auto rJObj = QJsonObject{{"receiver", message_info.receiver}};
    const auto sJObj = QJsonObject{{"sender", message_info.sender}};

    const QString addr = m_HostName + ":" + m_PortNum;
    const auto adJObj = QJsonObject{{"addr", addr}};

    const auto jArr = QJsonArray{dataJObj, rJObj, sJObj};

    /* const auto msgObj = QJsonObject{{"message", jArr}}; */
    const auto msgObj = QJsonObject{
        {"data", message_info.message},
        {"receiver", message_info.receiver},
        {"sender", message_info.sender},
        {"addr", addr},
        {"group", ""}
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
    const auto group = msgJson.value("group").toString();
    if(!group.isEmpty())
    {
        GroupMessage gm;
        gm.sender = sender;
        gm.groupName = group;
        gm.data = msg;
        gm.members = receiver.split(";").toVector();

        emit newGroupMessageArrived(gm);

        return;
    }
    
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

void Client::onSendGroupMessage(const GroupMessage& msg)
{
    QTcpSocket* socket = new QTcpSocket(this);
    socket->connectToHost(
        m_AppConfig.mainServerHostname,
        m_AppConfig.mainServerPort
    );

    if(!socket->waitForConnected(5000))
    {
        return;
    }

    const QString addr = m_HostName + ":" + m_PortNum;
    QString receiversString;

    for(const auto& receiver : msg.members)
    {
        receiversString += receiver;
        receiversString += ";";
    }

    /* QString senderStr = msg.groupName + ";" + msg.sender; */

    qDebug() << receiversString;

    const auto msgObj = QJsonObject{
        {"data", msg.data},
        {"receiver", receiversString},
        {"sender", msg.sender},
        {"addr", addr},
        {"group", msg.groupName}
    };
    const auto msgJsonDoc = QJsonDocument{msgObj};

    socket->write(msgJsonDoc.toJson());
    socket->close();

}
