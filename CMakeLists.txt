cmake_minimum_required(VERSION 3.27)
project(matrix_group01)

set(CMAKE_CXX_STANDARD 17)
# Отключаем, чтобы компилятор не избегал Move симантики.
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-elide-constructors")

add_executable(matrix_group01 main.cpp
        matrix.h
        matrix.cpp)
