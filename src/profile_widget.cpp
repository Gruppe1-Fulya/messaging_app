/**
 * @file profile_widget.cpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "messaging_application/profile_widget.hpp"

namespace ma
{

    ProfileWidget::ProfileWidget(const UserInfo& user_info, QWidget* parent)
        : QWidget(parent), m_UserInfo(user_info)
    {
        m_MainLayout = new QHBoxLayout();

        m_TextDisplayLayout = new QVBoxLayout();

        m_UserNameDisplay = new QLabel();
        m_UserNameDisplay->setText(user_info.username);

        m_UserEmailDisplay = new QLabel();
        m_UserEmailDisplay->setText(user_info.email);

        m_TextDisplayLayout->addWidget(m_UserNameDisplay);
        m_TextDisplayLayout->addWidget(m_UserEmailDisplay);

        m_MainLayout->addLayout(m_TextDisplayLayout);

        m_UserIconDisplay = new QLabel();
        m_MainLayout->addWidget(m_UserIconDisplay);

        this->setLayout(m_MainLayout);
    }

} // End of namespace ma.