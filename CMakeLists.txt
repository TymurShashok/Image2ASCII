cmake_minimum_required(VERSION 3.16)
project(Image2ASCII VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Указываем точный путь к OpenCV на твоем компьютере
set(OpenCV_DIR "C:/Users/PC/Downloads/prjectOpenCV/opencv/build/x64/vc16/lib")

# 2. Ищем библиотеку
find_package(OpenCV REQUIRED)

# 3. Перечисляем все твои файлы вручную, чтобы студия их точно увидела
add_executable(Image2ASCII 
    Image2ASCII.cpp
    ASCIIConverter.cpp
    ASCIIConverter.h
    Renderer.cpp
    Renderer.h
    Config.h
    Pixel.h
)

# 4. Связываем инклуды и линкер
target_include_directories(Image2ASCII PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(Image2ASCII PRIVATE ${OpenCV_LIBS})

# 5. Копируем DLL для запуска
if(WIN32)
    add_custom_command(TARGET Image2ASCII POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:Image2ASCII>
        $<TARGET_FILE_DIR:Image2ASCII>
        COMMAND_EXPAND_LISTS
    )
endif()
