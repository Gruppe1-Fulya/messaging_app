cmake_minimum_required(VERSION 3.0.0)
project(messaging_application)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt5 libraries.
find_package(Qt5 COMPONENTS Widgets Core Sql Network REQUIRED)
find_package(GTest REQUIRED)

set(SOURCES 
    src/program.cpp
    src/main_window.cpp
    src/central_widget.cpp
    src/chat_widget.cpp
    src/contacts_widget.cpp
    src/profile_widget.cpp
    src/db.cpp
    src/client.cpp
    include/${PROJECT_NAME}/main_window.hpp
    include/${PROJECT_NAME}/central_widget.hpp
    include/${PROJECT_NAME}/chat_widget.hpp
    include/${PROJECT_NAME}/contacts_widget.hpp
    include/${PROJECT_NAME}/profile_widget.hpp
    include/${PROJECT_NAME}/db.hpp
    include/${PROJECT_NAME}/client.hpp
    )

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Sql Qt5::Network)
target_include_directories(${PROJECT_NAME} PUBLIC include/)
