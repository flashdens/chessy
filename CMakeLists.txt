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
        src/io.c
        include/io.h
        src/generate.c
        include/generate.h
        src/validate.c
        include/validate.h
        src/makemove.c
        include/makemove.h
        include/perfthub.h
        src/perfthub.c
        include/perft.h
        src/perft.c
        src/main.c
        src/search.c
        include/search.h
        src/pvtable.c
        include/pvtable.h
        include/hashkeys.h
        include/board.h
)

target_include_directories(milochess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)