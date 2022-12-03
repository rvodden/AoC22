standard_build()

add_test(NAME day_3b COMMAND day_3b ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_3b PROPERTY PASS_REGULAR_EXPRESSION "2342" )