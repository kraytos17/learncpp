cmake_minimum_required(VERSION 3.28)

enable_language(CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_DEBUG_POSTFIX "-d")
set(CMAKE_CXX_E XTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(learn)

add_executable(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_sources(${PROJECT_NAME} PRIVATE
    src/bits.cpp
    src/main.cpp
    src/rand.cpp
    src/rand.hpp
    src/temp.cpp
    src/op_overload.cpp
    src/ip_overload.cpp
    src/class.cpp
    src/pv.cpp
    src/monster.cpp
    src/hangman.cpp
    src/animal.cpp
    src/potion.cpp
    src/sort.cpp
    src/names.cpp
    src/lambda.cpp
)

# if(CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
#   target_compile_options(${PROJECT_NAME} PRIVATE
#     -Wall -Wextra -Wpedantic -Wconversion -Werror=return-type -Wunused
#   )
# endif()
