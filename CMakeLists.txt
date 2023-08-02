cmake_minimum_required(VERSION 3.23)
project(milochess LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)

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
        src/io.c include/io.h src/generate.c include/generate.h src/validate.c include/validate.h
        src/makemove.c
        include/makemove.h)

target_include_directories(milochess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

