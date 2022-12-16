standard_build()

add_test(NAME "day_15a.command" COMMAND day_15 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_15a.command" PROPERTY PASS_REGULAR_EXPRESSION "5142231" )

add_test(NAME "day_15b.command" COMMAND day_15 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_15b.command" PROPERTY PASS_REGULAR_EXPRESSION "10884459367718")
