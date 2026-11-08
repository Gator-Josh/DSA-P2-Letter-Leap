cmake_minimum_required(VERSION 3.20)
project(LetterLeap)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(
        letter_leap src/main.cpp
        src/Trie.cpp
        src/Trie.h
        src/BK_Tree.cpp
        src/BK_Tree.h
        src/wordLoader.cpp
        src/wordLoader.h
)
