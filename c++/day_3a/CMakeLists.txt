standard_build()

add_test(NAME day_3a COMMAND day_3a ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_3a PROPERTY PASS_REGULAR_EXPRESSION "8153" )