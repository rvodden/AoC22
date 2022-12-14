standard_build()

add_test(NAME "day_14a.command" COMMAND day_14 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_14a.command" PROPERTY PASS_REGULAR_EXPRESSION "763" )

add_test(NAME "day_14b.command" COMMAND day_14 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_14b.command" PROPERTY PASS_REGULAR_EXPRESSION "23921")
