add_library(lib_day_2a day_2a.cpp)
add_executable(day_2a main.cpp)
add_executable(day_2a_test day_2a_test.cpp)

target_link_libraries(
    day_2a_test
    lib_day_2a
    GTest::gtest_main
)

target_link_libraries(
    day_2a
    lib_day_2a
)