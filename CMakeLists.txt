cmake_minimum_required(VERSION 3.20)
project(LetterLeap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(src)

add_executable(letter_leap
    src/main.cpp
    src/Trie.cpp
    src/Trie.h
    src/BK_Tree.cpp
    src/WordLoader.cpp
    src/WordLoader.h
    src/mainwindow.h src/mainwindow.cpp src/mainwindow.ui
    src/homepage.h src/homepage.cpp src/homepage.ui
    src/playpage.h src/playpage.cpp src/playpage.ui

)

target_link_libraries(letter_leap PRIVATE Qt6::Widgets)