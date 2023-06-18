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
#include <QString>

struct MessageInfo
{
    QString message;
    QString sender;
    QString receiver;

}; Q_DECLARE_METATYPE(MessageInfo)

#endif // DEFINITIONS_HPP_