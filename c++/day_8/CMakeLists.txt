standard_build()

add_test(NAME day_8a COMMAND day_8 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_8a PROPERTY PASS_REGULAR_EXPRESSION "1546" )

add_test(NAME day_8b COMMAND day_8 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_8b PROPERTY PASS_REGULAR_EXPRESSION "224" )
