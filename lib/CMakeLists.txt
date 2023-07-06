project(google_tests)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(google_tests_run ${CMAKE_SOURCE_DIR}/tests/test1.cpp)
target_link_libraries(google_tests_run gtest gtest_main)