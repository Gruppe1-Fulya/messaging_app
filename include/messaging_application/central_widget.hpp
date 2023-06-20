/**
 * @file central_widget.hpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CENTRAL_WIDGET_HPP
#define CENTRAL_WIDGET_HPP

#include <QWidget>
#include <QObject>
#include <QHBoxLayout>

#include "chat_widget.hpp"
#include "contacts_widget.hpp"
#include "profile_widget.hpp"
#include "db.hpp"
#include "client.hpp"
#include "group_chat_widget.hpp"

#include <yaml-cpp/yaml.h>

namespace ma
{


    class CentralWidget : public QWidget
    {
        Q_OBJECT

        public:

        CentralWidget(const QString& config_file_path, QWidget* parent = nullptr);
        ~CentralWidget();

        void createUI();

        void setConfigFilePath(const QString& config_file_path)
        {
            m_ConfigFilePath = config_file_path;
        }

        private:

        QString m_ConfigFilePath;

        QHBoxLayout* m_MainLayout;

        QVBoxLayout* m_ProfileAndContactsLayout;

        ChatWidget* m_ChatWidget;
        ContactsWidget* m_ContactsWidget;
        GroupChatList* m_GroupChatList;
        ProfileWidget* m_ProfileWidget;

        DatabaseHelper* m_DatabaseHelper;

        Client* m_Client;

    };
}

#endif // CENTRAL_WIDGET_HPP 