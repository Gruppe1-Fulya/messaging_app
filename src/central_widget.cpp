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

        m_ChatWidget = new ChatWidget(this);

        m_MainLayout->addWidget(m_ChatWidget);

        this->setLayout(m_MainLayout);

    }

}
