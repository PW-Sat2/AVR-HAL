set(NAME hal_mcu)
add_library(${NAME} INTERFACE)

target_include_directories(${NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/${MCU_INCLUDE}
)
