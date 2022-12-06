include(GoogleTest)

macro(standard_build)

    ## Library Build

    get_filename_component(DirectoryName ${CMAKE_CURRENT_SOURCE_DIR} NAME)    
    
    set(LibraryName "lib_${DirectoryName}")

    message(CHECK_START "Loading ${LibraryName}...")

    file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
    foreach(SOURCE_FILE ${SOURCE_FILES})
        message("   Adding source file: ${SOURCE_FILE}")
    endforeach()
    add_library(${LibraryName} SHARED ${SOURCE_FILES})

    target_link_libraries(${LibraryName} PRIVATE compiler_flags)
    target_include_directories(${LibraryName} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> $<INSTALL_INTERFACE:include>)
    string(TOUPPER ${LibraryName} UpperLibraryName)
    target_compile_definitions(${LibraryName} PRIVATE "EXPORTING_${UpperLibraryName}")

    ## Test Build

    set(TestName "${DirectoryName}_test")
    
    file(GLOB_RECURSE TEST_SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/test/*.hpp)
    foreach(SOURCE_FILE ${TEST_SOURCE_FILES})
        message("   Adding test source file: ${SOURCE_FILE}")
    endforeach()
    add_executable(${TestName} ${TEST_SOURCE_FILES})

    target_link_libraries(${TestName} PRIVATE compiler_flags)
    target_link_libraries(${TestName} PUBLIC ${LibraryName})
    target_link_libraries(${TestName} PUBLIC gtest)
    target_link_libraries(${TestName} PUBLIC gmock)
    target_link_libraries(${TestName} PUBLIC gtest_main)

    gtest_discover_tests(${TestName} XML_OUTPUT_DIR report EXTRA_ARGS --gtest_catch_exceptions=0)
    message(CHECK_PASS "done.")

    set(LibraryName ${LibraryName} PARENT_SCOPE)

    ## Executable Build

    set(ExecutableName "${DirectoryName}")
    file(GLOB_RECURSE EXECUTABLE_SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
    add_executable(${ExecutableName} ${EXECUTABLE_SOURCE_FILES})
    target_link_libraries(${ExecutableName} PUBLIC ${LibraryName})
    target_link_libraries(${ExecutableName} PUBLIC lib_common)

endmacro()

list( APPEND skip_directories cmake-* )
list( APPEND skip_directories cmake )
list( APPEND skip_directories build )
list( APPEND skip_directories python )

macro(subdir_list result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            set(skip OFF)
            if(child MATCHES "^\\..*")
                set(skip ON)
            endif()
            foreach(skip_dir ${skip_directories})
                if(child MATCHES ${skip_dir})
                    set(skip ON)
                endif()
            endforeach()
            if(NOT skip)
                LIST(APPEND dirlist ${child})
            endif()
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()