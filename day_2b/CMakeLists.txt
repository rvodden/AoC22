add_library(lib_day_2b day_2b.cpp)
add_executable(day_2b main.cpp)
add_executable(day_2b_test day_2b_test.cpp)

target_link_libraries(
    day_2b_test
    lib_day_2b
    GTest::gtest_main
)

target_link_libraries(
    day_2b
    lib_day_2b
)

gtest_discover_tests(day_2b_test)