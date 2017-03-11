set(NAME terminal)

add_library(${NAME} STATIC
    terminal.cpp
)

target_link_libraries(${NAME}
    libs
)
target_include_directories(${NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)
