cmake_minimum_required(VERSION 3.15.0)
project(qt-cam-app VERSION 0.2.0)

message(STATUS ${CMAKE_CXX_COMPILER})
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (${CMAKE_CXX_COMPILER} STREQUAL "/usr/bin/g++")
    set(CMAKE_CROSSCOMPILING FALSE)
    set(OpenCV_DIR /home/rudi/opencv-build/)
elseif(${CMAKE_CXX_COMPILER} STREQUAL "/usr/bin/aarch64-linux-gnu-g++-9")
    set(CMAKE_CROSSCOMPILING TRUE)
    set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/etc/lib/aarch64-linux-gnu/cmake/opencv4)
    set(OpenCV_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/etc/include/opencv4)
    set(Additional_LIBS ${CMAKE_SOURCE_DIR}/etc/lib/aarch64-linux-gnu/)
    include_directories(${OpenCV_INCLUDE_DIRS})
    link_directories(${Additional_LIBS})
else()
    message(ERROR ${CMAKE_CXX_COMPILER} " unsupported CXX Compiler")
endif()

message(STATUS "folder: " ${OpenCV_DIR})

find_package(Qt6 COMPONENTS Quick REQUIRED)
find_package(OpenCV REQUIRED )

set(RESOURCE ${CMAKE_SOURCE_DIR}/resources.qrc)

qt_add_resources(RESOURCE_ADDED ${RESOURCE})

qt_add_executable(qt-cam-app
    main.cpp
    opencvimageprovider.cpp
    opencvimageprovider.h
    videostreamer.cpp
    videostreamer.h
    ${RESOURCE_ADDED}
)

target_compile_definitions(qt-cam-app
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(qt-cam-app
    PRIVATE Qt6::Quick
    PRIVATE ${OpenCV_LIBS})

# Copy the distribution files
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/dist)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/bin)

add_custom_command(TARGET qt-cam-app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:qt-cam-app> "${CMAKE_SOURCE_DIR}/dist/bin"
)
