add_library(lib_day_3a day_3a.cpp)
add_executable(day_3a main.cpp)
add_executable(day_3a_test day_3a_test.cpp)

target_link_libraries(
    day_3a_test
    lib_day_3a
    GTest::gtest_main
)

target_link_libraries(
    day_3a
    lib_day_3a
)

gtest_discover_tests(day_3a_test)