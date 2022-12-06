standard_build()

add_test(NAME day_2a COMMAND day_2a ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_2a PROPERTY PASS_REGULAR_EXPRESSION "12679" )