cmake_minimum_required(VERSION 3.15.0)
project(qt-cam-app VERSION 0.2.0)

#include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Quick REQUIRED)
find_package(OpenCV REQUIRED )

#has to be included if qt6 was build by conan install command
#include_directories(${CONAN_INCLUDE_DIRS}/qt})
include_directories(${OpenCV_INCLUDE_DIRS})

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
    PRIVATE ${OpenCV_LIBS} )
