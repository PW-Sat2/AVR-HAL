set(NAME terminal)

add_library(${NAME} STATIC
    terminal.cpp
)

target_link_libraries(${NAME}
    hal_libs
)
