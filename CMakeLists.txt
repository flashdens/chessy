cmake_minimum_required(VERSION 3.23)
project(milochess LANGUAGES C CXX)
set(CMAKE_C_STANDARD 17)


add_executable(milochess
        include/board.h
        src/board.c
        src/init.c
        src/bitboards.c
        src/hashkeys.c
        src/utils.c
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
        include/hashkeys.h
        include/pvtable.h
        src/pvtable.c
        src/evaluate.c
        include/evaluate.h
        include/milochess.h
)

target_include_directories(milochess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
