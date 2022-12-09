standard_build()

add_test(NAME day_9a COMMAND day_9 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_9a PROPERTY PASS_REGULAR_EXPRESSION "6464" )

add_test(NAME day_9b COMMAND day_9 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_9b PROPERTY PASS_REGULAR_EXPRESSION "2604" )
