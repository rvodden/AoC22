cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(advent_of_code_2022 VERSION 0.0.1 LANGUAGES CXX)

cmake_policy(SET CMP0135 NEW)


set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)

include(StandardBuild)
include(FetchContent)

### Find Dependencies ###

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)
enable_testing()

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(compiler_flags INTERFACE
        "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused;-fdiagnostics-color=always;-O0>>"
        "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
        )

if (USE_SANITIZER STREQUAL "Address")
    target_compile_options(compiler_flags INTERFACE "-fsanitize=address")
    target_link_options(compiler_flags INTERFACE "-fsanitize=address")
elseif (USE_SANITIZER STREQUAL "Thread")
    target_compile_options(compiler_flags INTERFACE "-fsanitize=thread")
    target_link_options(compiler_flags INTERFACE "-fsanitize=thread")
elseif (USE_SANITIZER STREQUAL "Leak")
    target_compile_options(compiler_flags INTERFACE "-fsanitize=leak")
    target_link_options(compiler_flags INTERFACE "-fsanitize=leak")
elseif (USE_SANITIZER STREQUAL "Memory")
    target_compile_options(compiler_flags INTERFACE "-fsanitize=memory")
    target_link_options(compiler_flags INTERFACE "-fsanitize=memory")
elseif (USE_SANITIZER STREQUAL "Undefined")
    target_compile_options(compiler_flags INTERFACE "-fsanitize=undefined")
    target_link_options(compiler_flags INTERFACE "-fsanitize=undefined")
endif()

if (USE_GPROF)
    target_compile_options(compiler_flags INTERFACE "-pg")
    target_link_options(compiler_flags INTERFACE "-pg")
endif()


subdir_list(SUBDIRS ${MY_CURRENT_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
foreach(subdir ${SUBDIRS})
    add_subdirectory(${subdir})
endforeach()



if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include(CodeCoverage)
    SET(CODE_COVERAGE_VERBOSE)
    setup_target_for_coverage_gcovr_xml(${PROJECT_NAME}_coverage NAME coverage)

    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"
