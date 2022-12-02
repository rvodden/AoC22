add_library(lib_day_1b day_1b.cpp)
add_executable(day_1b main.cpp)
add_executable(day_1b_test day_1b_test.cpp)

target_link_libraries(
    day_1b_test
    lib_day_1b
    GTest::gtest_main
)

target_link_libraries(
    day_1b
    lib_day_1b
)

gtest_discover_tests(day_1b_test)