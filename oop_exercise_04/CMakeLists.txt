set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
cmake_minimum_required(VERSION 2.8) # Проверка версии CMake.
project(oop_exercise_04) # Название проекта
set(SOURCE_EXE main.cpp figure.hpp) # Установка переменной со списком исходников для исполняемого файла
add_executable(oop_exercise_04 ${SOURCE_EXE}) # Создает исполняемый файл с именем main
