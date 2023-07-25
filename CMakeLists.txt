cmake_minimum_required(VERSION 3.23)
project(milochess LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)

add_subdirectory(lib)
add_executable(milochess src/main.c src/init.c src/bitboards.c include/bitboards.h include/hashkeys.h src/hashkeys.c src/utils.c src/board.c src/data.c include/data.h)

target_include_directories(milochess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_directories(milochess PUBLIC include)
