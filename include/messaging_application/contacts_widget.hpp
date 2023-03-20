/**
 * @file contacts_widget.hpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CONTACTS_WIDGET_HPP
#define CONTACTS_WIDGET_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QPushButton>
#include <QDir>

#include <functional>

namespace ma
{
    class Contact : public QListWidgetItem
    {
        Q_OBJECT

        public:

        Contact(
            const QString& email,
            const QString& user_name
        );

        inline const QString getContactEmail() const
        {
            return m_Email;
        }

        inline const QString getContactName() const
        {
            return m_ContactName;
        }

        private:

        QString m_ContactName;

        QString m_Email;

    };

    class ContactsWidget : public QWidget
    {
        Q_OBJECT

        public:

        ContactsWidget(QWidget* parent = nullptr);

        void loadContacts();

        signals:

        void createContact(const QString& contact_id_to_emit);

        void openChat(const QString& contact_id);

        public slots:

        private:

        QListWidget* m_ContactsList;

        QPushButton* m_AddContactBtn;

        QVBoxLayout* m_MainLayout;

        void getContactInfo();

        void addContactToList(const QString& contact_id);

        void openChatWindowReq();

    }; 
}

#endif // CONTACTS_WIDGET_HPP