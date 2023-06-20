/**
 * @file definitions.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef DEFINITIONS_HPP_
#define DEFINITIONS_HPP_

#include <QObject>
#include <QVector>
#include <QPair>
#include <QString>

struct MessageInfo
{
    QString message;
    QString sender;
    QString receiver;

}; Q_DECLARE_METATYPE(MessageInfo)

struct TcpConfig
{
    QString tcpServerHostname;
    quint16 tcpServerPort;
    QString mainServerHostname;
    quint16 mainServerPort;
};

struct AppConfig
{
    QString username;
    QString email;
};

struct ChatHistory
{

    QVector<QPair<QString, QString>> messages;
/*     QVector<QString> userMsgs;
    QVector<QString> otherMsgs; */
}; Q_DECLARE_METATYPE(ChatHistory)

struct GroupInfo
{
    QString groupName;
    QVector<QString> members;
}; Q_DECLARE_METATYPE(GroupInfo);

struct GroupMessage
{
    QString data;
    QString groupName;
    QString sender;
    QVector<QString> members;
}; Q_DECLARE_METATYPE(GroupMessage);

#endif // DEFINITIONS_HPP_