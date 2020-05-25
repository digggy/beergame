cmake_minimum_required(VERSION 3.5)

project(beer-game LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(EXISTS $ENV{HOME}/Qt/5.14.2/gcc_64)
  set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.14.2/gcc_64)
endif()


find_package(Qt5 COMPONENTS Widgets Network Gui Core Charts WebEngineWidgets REQUIRED)

SET(COMMON_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/playerinterface.h
    ${CMAKE_SOURCE_DIR}/src/playerinterface.cpp
    ${CMAKE_SOURCE_DIR}/src/playerinterface.h
    ${CMAKE_SOURCE_DIR}/src/playerinterface.ui
    ${CMAKE_SOURCE_DIR}/src/instructorwindow.cpp
    ${CMAKE_SOURCE_DIR}/src/instructorwindow.h
    ${CMAKE_SOURCE_DIR}/src/instructorwindow.ui
    ${CMAKE_SOURCE_DIR}/src/instructor.h
    ${CMAKE_SOURCE_DIR}/src/instructor.cpp
    ${CMAKE_SOURCE_DIR}/src/player.h
    ${CMAKE_SOURCE_DIR}/src/player.cpp
    ${CMAKE_SOURCE_DIR}/src/playerevent.h
    ${CMAKE_SOURCE_DIR}/src/game.h
    ${CMAKE_SOURCE_DIR}/src/game.cpp
    ${CMAKE_SOURCE_DIR}/src/order.h
    ${CMAKE_SOURCE_DIR}/src/order.cpp
    ${CMAKE_SOURCE_DIR}/src/shipment.h
    ${CMAKE_SOURCE_DIR}/src/shipment.cpp
    ${CMAKE_SOURCE_DIR}/src/server/beergameserver.h
    ${CMAKE_SOURCE_DIR}/src/server/beergameserver.cpp
    ${CMAKE_SOURCE_DIR}/src/server/playerinterfaceserver.h
    ${CMAKE_SOURCE_DIR}/src/server/playerinterfaceserver.cpp
)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(docs)

enable_testing()
add_test(NAME misc COMMAND tests)
