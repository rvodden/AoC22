standard_build()

add_test(NAME "day_10a.command" COMMAND day_10 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_10a.command" PROPERTY PASS_REGULAR_EXPRESSION "15260" )

add_test(NAME "day_10b.command" COMMAND day_10 ${CMAKE_CURRENT_LIST_DIR}/input.txt)
set_property(TEST "day_10b.command" PROPERTY PASS_REGULAR_EXPRESSION "###...##..#..#.####..##..#....#..#..##..\n#..#.#..#.#..#.#....#..#.#....#..#.#..#.\n#..#.#....####.###..#....#....#..#.#....\n###..#.##.#..#.#....#.##.#....#..#.#.##.\n#....#..#.#..#.#....#..#.#....#..#.#..#.\n#.....###.#..#.#.....###.####..##...###.\n")
