set(NAME periph)
add_library(${NAME} STATIC
    eeprom.cpp
)

target_link_libraries(${NAME}
    libs
)

target_include_directories(${NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)
