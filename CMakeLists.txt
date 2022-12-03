cmake_minimum_required(VERSION 3.14)
project(advent_of_code_2022)

cmake_policy(SET CMP0135 NEW)

set(VERBOSE)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)
enable_testing()

add_subdirectory(day_1a)
add_subdirectory(day_1b)
add_subdirectory(day_2a)
add_subdirectory(day_2b)
add_subdirectory(day_3a)
add_subdirectory(day_3b)

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include(CodeCoverage)
    SET(CODE_COVERAGE_VERBOSE)
    setup_target_for_coverage_gcovr_xml(${PROJECT_NAME}_coverage NAME coverage)

    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"
