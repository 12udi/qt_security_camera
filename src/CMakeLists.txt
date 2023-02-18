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

qt_add_executable(${TARGET_NAME}
    ${SOURCES}
    ${HEADERS}
    ${RESOURCE_ADDED}
    )

target_compile_definitions(${TARGET_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${TARGET_NAME}
    PRIVATE Qt6::Core
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Gui
    PRIVATE Qt6::Qml
    PRIVATE ${OpenCV_LIBS})

# Copy the distribution files
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/dist)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/dist/bin)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}> "${PROJECT_SOURCE_DIR}/dist/bin"
    )
