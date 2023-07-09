project(google_tests)

add_subdirectory(googletest)


add_executable(google_tests_run ${CMAKE_SOURCE_DIR}/tests/test1.cpp ../tests/test_macros.cpp ../tests/test_init.cpp)

target_link_libraries(google_tests_run gtest gtest_main)

target_include_directories(google_tests_run PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_include_directories(google_tests_run PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_directories(google_tests_run PUBLIC ${CMAKE_SOURCE_DIR}/include)