standard_build()

message("   Customizing ${LibraryName}.")

find_package(OpenCL REQUIRED)
target_link_libraries(${LibraryName} PUBLIC OpenCL::OpenCL)
set(CL_HPP_TARGET_OPENCL_VERSION 210)

set(COPIED_KERNELS "")
file(GLOB KERNELS src/*.cl)
foreach(CurrentKernel IN LISTS KERNELS)
    cmake_path(GET CurrentKernel FILENAME FileName)
    add_custom_command(
                COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CurrentKernel}" "${CMAKE_CURRENT_BINARY_DIR}/${FileName}"
                OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${FileName}"
                DEPENDS "${CurrentKernel}"
                COMMENT "Copying kernel: ${CurrentKernel}"
                VERBATIM)
    list(APPEND COPIED_KERNELS ${CMAKE_CURRENT_BINARY_DIR}/${FileName})
endforeach()

add_custom_target(${LibraryName}_Kernels ALL DEPENDS ${COPIED_KERNELS})
add_dependencies(${LibraryName} ${LibraryName}_Kernels)
