standard_build()

add_test(NAME "day_13a.command" COMMAND day_13 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_13a.command" PROPERTY PASS_REGULAR_EXPRESSION "5605" )

add_test(NAME "day_13b.command" COMMAND day_13 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_13b.command" PROPERTY PASS_REGULAR_EXPRESSION "24969")
