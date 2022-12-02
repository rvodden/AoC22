add_library(lib_day_1a day_1a.cpp)
add_executable(day_1a main.cpp)
add_executable(day_1a_test day_1a_test.cpp)

target_link_libraries(
    day_1a_test
    lib_day_1a
    GTest::gtest_main
)

target_link_libraries(
    day_1a
    lib_day_1a
)

gtest_discover_tests(day_1a_test)