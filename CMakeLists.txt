 cmake_minimum_required(VERSION 3.0)
 project(qt_security_camera)

 set(CONAN_DISABLE_CHECK_COMPILER TRUE)
 set(CMAKE_CXX_STANDARD 17)

 add_definitions("-std=c++11")

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()

 add_executable(main main.cpp)
 target_link_libraries(main ${CONAN_LIBS})
