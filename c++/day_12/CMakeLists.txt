standard_build()

add_test(NAME "day_12a.command" COMMAND day_12 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_12a.command" PROPERTY PASS_REGULAR_EXPRESSION "15260" )

add_test(NAME "day_12b.command" COMMAND day_12 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_12b.command" PROPERTY PASS_REGULAR_EXPRESSION "12345")
