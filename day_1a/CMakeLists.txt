standard_build()

add_test(NAME day_1b COMMAND day_1b ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_1b PROPERTY PASS_REGULAR_EXPRESSION "66616" )