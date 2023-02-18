set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

enable_testing(true)

add_executable(test_${TARGET_NAME}
    ../../src/VideoStreamer.cpp
    TestVideoStreamer.cpp
    )

add_test(NAME test_${TARGET_NAME}
    COMMAND test_${TARGET_NAME}
    )

target_link_libraries(test_${TARGET_NAME}
    PRIVATE Qt6::Core
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Gui
    PRIVATE Qt6::Qml
    PRIVATE ${CONAN_LIBS}
    PRIVATE ${OpenCV_LIBS}
    )
