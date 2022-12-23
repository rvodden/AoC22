standard_build()

find_package(TBB REQUIRED)
target_link_libraries(${LibraryName} PUBLIC TBB::tbb)

add_test(NAME "day_19a.command" COMMAND day_16 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_19a.command" PROPERTY PASS_REGULAR_EXPRESSION "2341" )

add_test(NAME "day_19b.command" COMMAND day_16 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_19b.command" PROPERTY PASS_REGULAR_EXPRESSION "3689")
