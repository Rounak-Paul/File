cmake_minimum_required(VERSION 3.20)

project(FileExample LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(FileTest
    Test/main.cpp 
    Include/File.h
)

target_include_directories(FileTest PUBLIC 
    Include
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(FileTest PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(FileTest PRIVATE /W4)
endif()