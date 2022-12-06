standard_build()

add_test(NAME day_1a COMMAND day_1a ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_1a PROPERTY PASS_REGULAR_EXPRESSION "66616" )