cmake_minimum_required(VERSION 3.16)

project(Image2ASCII VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(Image2ASCII
    Image2ASCII.cpp
    ASCIIConverter.cpp
    ASCIIConverter.h
    Renderer.cpp
    Renderer.h
    Config.h
    Pixel.h
)

target_include_directories(Image2ASCII PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(Image2ASCII PRIVATE
    ${OpenCV_LIBS}
)