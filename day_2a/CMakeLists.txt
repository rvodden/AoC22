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
    lib_common
    lib_day_2a
)

gtest_discover_tests(day_2a_test)

add_test(NAME day_2a COMMAND day_2a ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_2a PROPERTY PASS_REGULAR_EXPRESSION "12679" )