set(NAME hal)

add_library(${NAME} STATIC
    devices.h
    hal
    libs.h
    periph.h
)

target_include_directories(hal PUBLIC
    ../
)

add_subdirectory(devices)
add_subdirectory(libs)
add_subdirectory(mcu)
add_subdirectory(periph)

target_link_libraries(${NAME}
    hal_libs
    hal_mcu
    hal_periph
    hal_devices
)

if(HAL_BOARD)
    add_subdirectory(boards)
    target_link_libraries(${NAME}
        hal_board
    )
endif(HAL_BOARD)
