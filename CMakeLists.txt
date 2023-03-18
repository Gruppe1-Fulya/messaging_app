cmake_minimum_required(VERSION 3.0.0)
project(messaging_application)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt5 libraries.
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

set(SOURCES 
    src/program.cpp
    src/main_window.cpp
    src/central_widget.cpp
    include/${PROJECT_NAME}/main_window.hpp
    include/${PROJECT_NAME}/central_widget.hpp
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)
target_include_directories(${PROJECT_NAME} PUBLIC include/${PROJECT_NAME})
