standard_build()

add_test(NAME "day_16a.command" COMMAND day_16 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_16a.command" PROPERTY PASS_REGULAR_EXPRESSION "1647" )

# Takes 40 minutes to run :-(
# add_test(NAME "day_16b.command" COMMAND day_16 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
# set_property(TEST "day_16b.command" PROPERTY PASS_REGULAR_EXPRESSION "2169")
