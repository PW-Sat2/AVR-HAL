set(NAME hal_periph)
add_library(${NAME} STATIC
    MCU/eeprom.cpp
)

target_link_libraries(${NAME}
    hal_libs
)
