standard_build()

add_test(NAME "day_20a.command" COMMAND day_20 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_20a.command" PROPERTY PASS_REGULAR_EXPRESSION "1087" )

add_test(NAME "day_20b.command" COMMAND day_20 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_20b.command" PROPERTY PASS_REGULAR_EXPRESSION "13084440324666")
