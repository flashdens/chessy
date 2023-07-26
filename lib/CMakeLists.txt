project(google_tests)

add_subdirectory(googletest)

add_executable(google_tests_run ../tests/utils/FR2SQ.cpp ../tests/test_init.cpp ../tests/test_bitboard.cpp ../tests/test_board.cpp ../src/utils.c)
target_include_directories(google_tests_run PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_directories(google_tests_run PUBLIC ../include)
target_link_libraries(google_tests_run gtest_main)

