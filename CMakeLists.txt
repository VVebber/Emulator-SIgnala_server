cmake_minimum_required(VERSION 3.16)

project(Server VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES  Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt5 REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    server.h
    server.cpp
    wavesimulator.cpp
    wavesimulator.h
    mainwindow.h
    mainwindow.ui
    )

add_executable(Server
    ${PROJECT_SOURCES}
    )

target_link_libraries(Server PRIVATE Qt5::Widgets Qt5::Network)
