set(NAME hal)
add_library(${NAME} INTERFACE)

add_subdirectory(devices)
add_subdirectory(libs)
add_subdirectory(mcu)
add_subdirectory(periph)

target_link_libraries(${NAME} INTERFACE
    devices
    libs
    mcu
    periph
)

if(HAL_BOARD)
    add_subdirectory(boards)
    target_link_libraries(${NAME} INTERFACE
        board
    )
endif(HAL_BOARD)
