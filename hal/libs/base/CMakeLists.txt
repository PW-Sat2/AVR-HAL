set(NAME hal_base)

add_library(${NAME} STATIC
    system.h
    traits.h
    utils.h
)

target_link_libraries(${NAME} hal_libs)
