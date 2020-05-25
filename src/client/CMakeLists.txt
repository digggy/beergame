cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(beer-game)

set (CMAKE_BINARY_DIR .)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(beergame-client
    main.cpp
    clientinterface.cpp
    clientinterface.h
    ClientInterface.ui
    playerclient.cpp
    playerclient.h
    ../../resources/resources.qrc
)

target_link_libraries(beergame-client PRIVATE Qt5::Widgets Qt5::Charts Qt5::Network Qt5::Core Qt5::Gui)

