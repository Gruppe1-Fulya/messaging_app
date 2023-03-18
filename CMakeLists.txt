cmake_minimum_required(VERSION 3.0.0)
project(messaging_application)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt5 libraries.
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)