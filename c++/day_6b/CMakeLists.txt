standard_build()

add_test(NAME day_6b COMMAND day_6b ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_6b PROPERTY PASS_REGULAR_EXPRESSION "2145" )