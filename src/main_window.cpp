/**
 * @file main_window.cpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "messaging_application/main_window.hpp"

namespace ma
{
    MainWindow::MainWindow(const QString& config_file_path, QWidget *parent)
    {
        m_CentralWidget = new CentralWidget(config_file_path, this);
        this->setCentralWidget(m_CentralWidget);

    }
}

