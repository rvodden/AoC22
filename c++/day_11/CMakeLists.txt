standard_build()

add_test(NAME "day_11a.command" COMMAND day_11 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_11a.command" PROPERTY PASS_REGULAR_EXPRESSION "88208" )

add_test(NAME "day_11b.command" COMMAND day_11 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_11b.command" PROPERTY PASS_REGULAR_EXPRESSION "")
