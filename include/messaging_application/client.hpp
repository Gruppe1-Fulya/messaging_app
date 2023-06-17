/**
 * @file client.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <QTcpSocket>
#include <QTcpServer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QString>
#include <QDebug>

#include "messaging_application/definitions.hpp"

class Client : public QObject
{
    Q_OBJECT

    public:

    explicit Client(QObject* parent = nullptr);

    ~Client();

    signals:

    void newMessageArrived(const MessageInfo& message_info);

    public slots:

    void onSendMessage(const MessageInfo& message_info);
    
    void newConnection();

    void readyRead();

    void disconnected();
/* 
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead(); */

    private:

    QString m_HostName;
    
    uint16_t m_PortNum;
    
    QTcpServer* m_ListenerServer;

    QTcpSocket* m_Socket;
};


#endif // CLIENT_HPP_