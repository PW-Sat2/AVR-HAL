set(NAME hal_periph)

file(GLOB_RECURSE HAL_PERIPH_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)

add_library(${NAME} STATIC
    ${HAL_PERIPH_SOURCES}
)


target_link_libraries(${NAME}
    hal_libs
)
