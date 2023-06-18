/**
 * @file program.cpp
 * @author Eren Naci Odabasi enaciodabasi@outlook.com
 * @brief 
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <QApplication>

#include "messaging_application/definitions.hpp"
#include "messaging_application/main_window.hpp"

int main(int argc, char** argv)
{
    qRegisterMetaType<MessageInfo>();
    QApplication app(argc, argv);
    QApplication::setApplicationName("Messaging Application");

    ma::MainWindow* mw = new ma::MainWindow();
    mw->show();

    return app.exec();
}