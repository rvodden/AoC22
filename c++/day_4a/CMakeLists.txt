standard_build()

add_test(NAME day_4a COMMAND day_4a ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_4a PROPERTY PASS_REGULAR_EXPRESSION "509" )