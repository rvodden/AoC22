add_library(lib_day_3b day_3b.cpp)
add_executable(day_3b main.cpp)
add_executable(day_3b_test day_3b_test.cpp)

target_link_libraries(
    day_3b_test
    lib_day_3b
    GTest::gtest_main
)

target_link_libraries(
    day_3b
    lib_day_3b
)

gtest_discover_tests(day_3b_test)