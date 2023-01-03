cmake_minimum_required(VERSION 3.0.0)
project(qt_security_camera)

add_definitions("-std=c++11")

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

add_executable(camera_app main.cpp)
target_link_libraries(camera_app ${CONAN_LIBS})
