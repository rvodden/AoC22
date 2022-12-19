standard_build()

add_test(NAME "day_17a.command" COMMAND day_17 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_17a.command" PROPERTY PASS_REGULAR_EXPRESSION "1647" )

add_test(NAME "day_17b.command" COMMAND day_17 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_17b.command" PROPERTY PASS_REGULAR_EXPRESSION "10884459367718")
