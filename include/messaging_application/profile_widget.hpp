/**
 * @file profile_widget.hpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PROFILE_WIDGET_HPP
#define PROFILE_WIDGET_HPP

#include <QWidget>
#include <QObject>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>

namespace ma
{

    struct UserInfo
    {
        QString username;
        QString email;
    };

    class ProfileWidget : public QWidget
    {

        Q_OBJECT

        public:

        ProfileWidget(const UserInfo& user_info, QWidget* parent = nullptr);

        //~ProfileWidget();

        private:

        QHBoxLayout* m_MainLayout;

        QVBoxLayout* m_TextDisplayLayout;

        QLabel* m_UserNameDisplay;
        QLabel* m_UserEmailDisplay;
        QLabel* m_UserIconDisplay;


    };

} // End of namespace ma.

#endif // PROFILE_WIDGET_HPP