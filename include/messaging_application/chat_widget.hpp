/**
 * @file chat_widget.hpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CHAT_WIDGET_HPP
#define CHAT_WIDGET_HPP

#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QFrame>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QString>
#include <QLabel>
#include <QTextEdit>


#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

namespace ma
{

    class ChatTab;
    
    class ChatWidget : public QTabWidget
    {

        Q_OBJECT

        public:

        ChatWidget(QWidget* parent = nullptr);
        ~ChatWidget();

        int addChatTab(const QString& chat_name);

        private:

        std::unordered_map<std::string, ChatTab*> m_ChatTabs;        

    };

    /*
    -----------------------------------------
    -----------------------------------------
    -----------------------------------------
    */

    class ChatTab : public QWidget
    {
        Q_OBJECT

        public:

        ChatTab(
            const QString& chat_tab_name, 
            QWidget* parent = nullptr
        );
        ~ChatTab();

        inline const QString getTabName() const
        {
            return m_ChatTabName;
        }

        virtual void messageReceived(const QString& sender_name, const QString& message);

        private:

        QVBoxLayout* m_MainLayout;

        QGridLayout* m_MessageLayout;

        QHBoxLayout* m_SendMsgBoxLayout;

        QFrame* m_SendMsgBox;

        QFrame* m_MsgsFrame;

        QScrollArea* m_MsgsScrollArea;

        QTextEdit* m_TypeMsgBox;

        QPushButton* m_SendMsgBtn;
        
        int currRow = 0;

        QString m_ChatTabName;

        void sendMessage();
        

    };

    class GroupChatTab : public ChatTab
    {
        public:

        GroupChatTab(
            const QString& chat_tab_name, 
            QWidget* parent = nullptr
        );
        
        private:


    };

} // End of namespace ma

#endif // CHAT_WIDGET_HPP