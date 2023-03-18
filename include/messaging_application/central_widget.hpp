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

namespace ma
{
    class CentralWidget : public QWidget
    {
        Q_OBJECT

        public:

        CentralWidget(QWidget* parent = nullptr);

        private:

        QHBoxLayout* m_MainLayout;


    };
}

#endif // CENTRAL_WIDGET_HPP 