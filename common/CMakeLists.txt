add_library(lib_common)

target_sources(lib_common
    PRIVATE main.cpp
    PUBLIC main.hpp
)

target_include_directories(lib_common
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
)