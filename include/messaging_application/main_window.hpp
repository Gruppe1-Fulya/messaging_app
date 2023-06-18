/**
 * @file main_window.hpp
 * @author Eren Naci Odabasi enaciodabasi@outlook.com
 * @brief 
 * @version 0.1
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include "central_widget.hpp"

namespace ma // ma is short for Messaging Application.
{

    class MainWindow : public QMainWindow
    {

        Q_OBJECT

        public:

        /**
         * @brief Construct a new ma::MainWindow object
         * 
         * @param parent Pointer to the parent widget. 
         */
        MainWindow(const QString& config_file_path, QWidget* parent = nullptr);


        private:

        CentralWidget* m_CentralWidget;

    };

} // End of namespace ma.


#endif // MAIN_WINDOW_HPP