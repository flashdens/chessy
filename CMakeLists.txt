cmake_minimum_required(VERSION 3.23)
project(milochess LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)

add_subdirectory(lib)

add_executable(milochess
        src/init.c
        src/bitboards.c
        src/hashkeys.c
        src/utils.c
        src/board.c
        src/data.c
        src/attack.c
        src/move.c
        src/main.c
        src/io.c include/io.h)

target_include_directories(milochess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

