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

namespace ma
{
    class CentralWidget : public QWidget
    {
        Q_OBJECT

        public:

        CentralWidget(QWidget* parent = nullptr);

        private:

        QHBoxLayout* m_MainLayout;

        ChatWidget* m_ChatWidget;


    };
}

#endif // CENTRAL_WIDGET_HPP 