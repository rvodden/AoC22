standard_build()

add_test(NAME "day_18a.command" COMMAND day_18 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_18a.command" PROPERTY PASS_REGULAR_EXPRESSION "1647" )

add_test(NAME "day_18b.command" COMMAND day_18 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_18b.command" PROPERTY PASS_REGULAR_EXPRESSION "10884459367718")
