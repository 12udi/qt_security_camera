find_package(Qt6 COMPONENTS Quick Gui Qml Test REQUIRED)
find_package(OpenCV REQUIRED )

set(RESOURCE ${PROJECT_SOURCE_DIR}/src/resources.qrc)
qt_add_resources(RESOURCE_ADDED ${RESOURCE})

add_subdirectory(unittest)
