set(NAME hal)

add_library(${NAME} INTERFACE)

target_include_directories(hal INTERFACE
    ../
)

add_subdirectory(libs)
add_subdirectory(mcu)
add_subdirectory(periph)

target_link_libraries(${NAME} INTERFACE
    hal_libs
    hal_mcu
    hal_periph
)

if(HAL_BOARD)
    add_subdirectory(boards)
    target_link_libraries(${NAME} INTERFACE
        hal_board
    )
endif(HAL_BOARD)
