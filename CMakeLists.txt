cmake_minimum_required(VERSION 3.16)

project(Server VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Network Xml)

set(PROJECT_SOURCES
    src/main.cpp
    src/server.h
    src/server.cpp
    src/client.cpp
    src/client.h
    src/manager.h
    src/manager.cpp
    )

add_executable(Server
    ${PROJECT_SOURCES}
    src/protocol.h src/protocol.cpp
    src/protocoljson.h src/protocoljson.cpp
    src/protocolxml.h src/protocolxml.cpp
    src/command.h src/command.cpp
    )

target_link_libraries(Server PRIVATE Qt5::Core Qt5::Network Qt5::Xml)
