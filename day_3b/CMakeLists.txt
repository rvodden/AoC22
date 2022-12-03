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
    lib_common
    lib_day_3b
)

gtest_discover_tests(day_3b_test)

add_test(NAME day_3b COMMAND day_3b ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_3b PROPERTY PASS_REGULAR_EXPRESSION "2342" )