cmake_minimum_required(VERSION 3.5)

project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)

install(TARGETS main
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
