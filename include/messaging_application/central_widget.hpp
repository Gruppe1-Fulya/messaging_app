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

namespace ma
{
    class CentralWidget : public QWidget
    {
        Q_OBJECT

        public:

        CentralWidget(QWidget* parent = nullptr);
        ~CentralWidget();

        void createUI();

        private:

        QHBoxLayout* m_MainLayout;

        QVBoxLayout* m_ProfileAndContactsLayout;

        ChatWidget* m_ChatWidget;
        ContactsWidget* m_ContactsWidget;
        ProfileWidget* m_ProfileWidget;

        DatabaseHelper* m_DatabaseHelper;

        Client* client;

    };
}

#endif // CENTRAL_WIDGET_HPP 