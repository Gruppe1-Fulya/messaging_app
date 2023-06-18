/**
 * @file contacts_widget.cpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "messaging_application/contacts_widget.hpp"
#include <QDebug>
namespace ma
{
    ContactsWidget::ContactsWidget(QWidget* parent)
        : QWidget(parent)
    {
        
        m_MainLayout = new QVBoxLayout();

        m_AddContactBtn = new QPushButton("Add Contact");

        m_ContactsList = new QListWidget(this);
        m_MainLayout->addWidget(m_ContactsList, 90);
        m_MainLayout->addWidget(m_AddContactBtn, 10);

        connect(
            m_AddContactBtn,
            &QPushButton::clicked,
            this,
            &ContactsWidget::getContactInfo
        );

        connect(
            this,
            &ContactsWidget::createContact,
            this,
            &ContactsWidget::addContactToList
        );

        connect(
            m_ContactsList,
            &QListWidget::itemDoubleClicked,
            this,
            &ContactsWidget::openChatWindowReq
        );


        this->setLayout(m_MainLayout);

    }

    void ContactsWidget::getContactInfo()
    {
        bool ok;
        QString email = QInputDialog::getText(
            this,
            tr("Add Contact"),
            tr("E-Mail:"),
            QLineEdit::Normal,
            QDir::home().dirName(),
            &ok
        );

        if(ok && !email.isEmpty())
        {
            emit createContact(email);
        }


    }

    void ContactsWidget::addContactToList(const QString& contact_id)
    {
        // Get info from server regarding the email owner.

        QString name = contact_id;

        m_ContactsList->addItem(new QListWidgetItem(contact_id));

    }

    void ContactsWidget::openChatWindowReq(QListWidgetItem* item)
    {
        emit openChat(item->text());
    }

    void ContactsWidget::loadContacts(const QVector<QString>& contacts)
    {
        for(const auto& c : contacts)
        {
            m_ContactsList->addItem(
                new QListWidgetItem(c)
            );
        }
    }

}