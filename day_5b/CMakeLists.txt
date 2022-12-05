standard_build()

add_test(NAME day_5b COMMAND day_5b ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_5b PROPERTY PASS_REGULAR_EXPRESSION "NBTVTJNFJ" )