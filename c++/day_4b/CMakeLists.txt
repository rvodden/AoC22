standard_build()

add_test(NAME day_4b COMMAND day_4b ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_4b PROPERTY PASS_REGULAR_EXPRESSION "870" )