cmake_minimum_required(VERSION 3.8)

project(
    Lab7_Dijkstra
    LANGUAGES CXX
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -O2")

# Основной исполняемый файл
add_executable(main
    main.cpp
    dijkstra.cpp
)

# Подключаем заголовочные файлы из текущей директории
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})