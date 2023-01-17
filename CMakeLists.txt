cmake_minimum_required(VERSION 3.15.0)
project(qt-cam-app VERSION 0.2.0)

#has to be included if conan was involved in build
#include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# copied from prebuild RPi4 OpenCV install folder (usr/local/lib/aarch64-linux-gnu/cmake/opencv4)
set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/etc/lib/aarch64-linux-gnu/cmake/opencv4)

find_package(Qt6 COMPONENTS Quick REQUIRED)
find_package(OpenCV REQUIRED )

#has to be included if qt6 was build by conan install command
#include_directories(${CONAN_INCLUDE_DIRS}/qt})

# copied from prebuild RPi4 OpenCV install folder (usr/local/include/opencv4)
set(OpenCV_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/etc/include/opencv4)
include_directories(${OpenCV_INCLUDE_DIRS})

set(Additionals_LIBS ${CMAKE_SOURCE_DIR}/etc/lib/aarch64-linux-gnu/)
link_directories(${Additionals_LIBS})

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
    PRIVATE ${OpenCV_LIBS}
#    PRIVATE ${Additionals_LIBS}
    )

# Copy the distribution files
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/dist)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/bin)

add_custom_command(TARGET qt-cam-app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:qt-cam-app> "${CMAKE_SOURCE_DIR}/dist/bin"
    )

