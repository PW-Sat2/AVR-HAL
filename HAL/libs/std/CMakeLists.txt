#pragma GCC system_header
set(NAME stdlib)

add_library(${NAME} INTERFACE)

add_definitions("-w")

target_include_directories(${NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)
