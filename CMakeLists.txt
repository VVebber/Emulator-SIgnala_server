cmake_minimum_required(VERSION 3.16)

project(Server VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS  Network )

add_subdirectory(lib/ProtocolLib)

add_executable(server
  src/main.cpp
  src/server.h  src/server.cpp
  src/client.h  src/client.cpp
  src/manager.h src/manager.cpp
)

target_link_libraries(server PRIVATE Qt5::Network
protocol)
