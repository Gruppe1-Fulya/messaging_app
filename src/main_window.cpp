#include "main_window.hpp"

namespace ma
{
    MainWindow::MainWindow(QWidget *parent)
    {
        m_CentralWidget = new CentralWidget(this);
        this->setCentralWidget(m_CentralWidget);


    }
}

