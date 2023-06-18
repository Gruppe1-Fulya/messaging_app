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
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "messaging_application/definitions.hpp"
#include "messaging_application/main_window.hpp"

int main(int argc, char** argv)
{
    qRegisterMetaType<MessageInfo>();
    QApplication app(argc, argv);
    QApplication::setApplicationName("Messaging Application");

    QCommandLineParser parser;
    parser.setApplicationDescription("");
    parser.addPositionalArgument("source", QApplication::translate("main", "Source file to copy."));
    parser.addPositionalArgument("destination", QApplication::translate("main", "Destination directory."));
    
    QCommandLineOption configFilePathOption(
        QStringList() << "c" << "config-file",
        QApplication::translate("main", "Copy all source files into <directory>."),
        QApplication::translate("main", "directory")    
    );
    parser.addOption(configFilePathOption);

    parser.process(app);

    const QStringList args = parser.positionalArguments(); 

    QString configFilePath = parser.value(configFilePathOption);
    qDebug() << configFilePath;
    ma::MainWindow* mw = new ma::MainWindow(configFilePath);
    mw->show();

    return app.exec();
}