standard_build()

add_test(NAME day_6a COMMAND day_6a ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_6a PROPERTY PASS_REGULAR_EXPRESSION "1544" )