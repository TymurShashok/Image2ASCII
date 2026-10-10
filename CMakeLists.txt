
cmake_minimum_required(VERSION 3.20)

project(Image2ASCII VERSION 1.09 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# OpenCV
find_package(OpenCV REQUIRED)

# GoogleTest
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

add_library(Image2ASCII_core
    src/ASCIIConverter.cpp
    src/Renderer.cpp
    src/Input.cpp
)

target_include_directories(Image2ASCII_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(Image2ASCII_core PUBLIC
    ${OpenCV_LIBS}
)

add_executable(Image2ASCII
    src/Image2ASCII.cpp
    src/ASCIIConverter.cpp
    src/ASCIIConverter.h
    src/Renderer.cpp
    src/Renderer.h
    src/Input.h
    src/Input.cpp
    src/Config.h
    src/Pixel.h
    resources/app.rc
    resources/app.ico
)

target_link_libraries(Image2ASCII PRIVATE
    Image2ASCII_core
)


enable_testing()

add_executable(Image2ASCII_tests
    tests/ASCIIConverterTests.cpp
    tests/ConfigTests.cpp
    tests/InputTests.cpp
)

target_link_libraries(Image2ASCII_tests PRIVATE
    Image2ASCII_core
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Image2ASCII_tests)

# Copy runtime DLLs next to the application
if(WIN32)
    add_custom_command(TARGET Image2ASCII POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:Image2ASCII>
        $<TARGET_FILE_DIR:Image2ASCII>
        COMMAND_EXPAND_LISTS
    )
endif()
