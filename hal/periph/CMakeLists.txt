set(NAME periph)
add_library(${NAME} STATIC
    MCU/eeprom.cpp
)

target_link_libraries(${NAME}
    libs
)

# target_include_directories(${NAME} INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}/Analog
#     ${CMAKE_CURRENT_LIST_DIR}/GPIO
#     ${CMAKE_CURRENT_LIST_DIR}/I2C
#     ${CMAKE_CURRENT_LIST_DIR}/MCU
#     ${CMAKE_CURRENT_LIST_DIR}/Serial
#     ${CMAKE_CURRENT_LIST_DIR}/SPI
# )
