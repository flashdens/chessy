cmake_minimum_required(VERSION 3.23)
project(milochess)

set(CMAKE_C_STANDARD 17)

add_subdirectory(lib)
add_executable(milochess src/main.c)
