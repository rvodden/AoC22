standard_build()

add_test(NAME day_2b COMMAND day_2b ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_2b PROPERTY PASS_REGULAR_EXPRESSION "14470" )