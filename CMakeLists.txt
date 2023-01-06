cmake_minimum_required(VERSION 3.15.0)
project(qt-conan-project VERSION 0.1.0)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Quick REQUIRED)

qt_add_executable(qt-conan
    main.cpp
)

qt_add_qml_module(qt-conan
    URI qtconan
    VERSION 1.0
    QML_FILES qml/main_ui.qml
)

target_compile_definitions(qt-conan
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(qt-conan
    PRIVATE Qt6::Quick)
