#include "messaging_application/main_window.hpp"

namespace ma
{
    MainWindow::MainWindow(const QString& config_file_path, QWidget *parent)
    {
        m_CentralWidget = new CentralWidget(config_file_path, this);
        this->setCentralWidget(m_CentralWidget);

    }
}

