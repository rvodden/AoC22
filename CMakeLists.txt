cmake_minimum_required(VERSION 3.14)
project(advent_of_code_2022)

cmake_policy(SET CMP0135 NEW)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_subdirectory(day_1a)
add_subdirectory(day_1b)
add_subdirectory(day_2a)
add_subdirectory(day_2b)