set(NAME hal)
add_library(${NAME} INTERFACE)

add_subdirectory(boards)
add_subdirectory(mcu)
add_subdirectory(libs)
add_subdirectory(periph)

target_link_libraries(${NAME} INTERFACE
    board
    mcu
    libs
    periph
)

target_include_directories(${NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/devices
)
