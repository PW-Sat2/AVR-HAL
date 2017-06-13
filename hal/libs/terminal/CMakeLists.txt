set(NAME terminal)

add_library(${NAME} STATIC
    terminal.cpp
    terminal.h
)

target_link_libraries(${NAME}
    hal_libs
)
