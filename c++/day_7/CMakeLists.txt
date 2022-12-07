standard_build()

add_test(NAME day_7a COMMAND day_7 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_7a PROPERTY PASS_REGULAR_EXPRESSION "1315285" )

add_test(NAME day_7b COMMAND day_7 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_7a PROPERTY PASS_REGULAR_EXPRESSION "9847279" )