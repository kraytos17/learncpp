cmake_minimum_required(VERSION 3.28.2)
project(learn)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(.)

add_executable(learn
        bits.cpp
        main.cpp
        rand.cpp
        rand.hpp
        temp.cpp
        op_overload.cpp
        ip_overload.cpp
        class.cpp
        pv.cpp
        monster.cpp
        hangman.cpp
        animal.cpp
)
