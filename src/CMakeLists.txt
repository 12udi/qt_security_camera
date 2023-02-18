set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Quick Gui Qml Test REQUIRED)
find_package(OpenCV REQUIRED )

set(RESOURCE ${PROJECT_SOURCE_DIR}/src/resources.qrc)
qt_add_resources(RESOURCE_ADDED ${RESOURCE})

set(SOURCES
    main.cpp
    OpencvImageProvider.cpp
    VideoStreamer.cpp
    )

set(HEADERS
    OpencvImageProvider.h
    VideoStreamer.h
    )

qt_add_executable(qt-cam-app
    ${SOURCES}
    ${HEADERS}
    ${RESOURCE_ADDED}
    )

target_compile_definitions(qt-cam-app
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(qt-cam-app
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Gui
    PRIVATE Qt6::Qml
    PRIVATE Qt6::Test
    PRIVATE ${OpenCV_LIBS})

# Copy the distribution files
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/dist)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/dist/bin)

add_custom_command(TARGET qt-cam-app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:qt-cam-app> "${PROJECT_SOURCE_DIR}/dist/bin"
    )
