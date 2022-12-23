standard_build()

target_link_libraries(${LibraryName} PRIVATE gtest)

add_standard_test("a" "27436")
add_standard_test("b" "15426")
