standard_build()

add_test(NAME day_5a COMMAND day_5a ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST day_5a PROPERTY PASS_REGULAR_EXPRESSION "QMBMJDFTD" )