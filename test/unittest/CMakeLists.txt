find_package(Qt6 REQUIRED COMPONENTS Test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

enable_testing(true)

add_executable(test_qt_cam_app 
TestVideoStreamer.cpp
)

add_test(NAME test_qt_cam_app 
COMMAND test_qt_cam_app
)

target_link_libraries(test_qt_cam_app
PRIVATE Qt::Test
)