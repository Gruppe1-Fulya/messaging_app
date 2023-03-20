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
#include "central_widget.hpp"

namespace ma
{

    CentralWidget::CentralWidget(QWidget *parent)
    {
        m_MainLayout = new QHBoxLayout(this);

        m_ContactsWidget = new ContactsWidget(this);
        m_ChatWidget = new ChatWidget(this);

        m_MainLayout->addWidget(m_ChatWidget, 80);
        m_MainLayout->addWidget(m_ContactsWidget, 20);
        this->setLayout(m_MainLayout);

        connect(
            m_ContactsWidget,
            &ContactsWidget::openChat,
            m_ChatWidget,
            &ChatWidget::addChatTab  
        );

    }

}
