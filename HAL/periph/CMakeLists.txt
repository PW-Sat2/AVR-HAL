set(NAME periph)
add_library(${NAME} STATIC
    eeprom.cpp
)

add_subdirectory(Serial)

target_link_libraries(${NAME} PUBLIC
    libs
    Serial
)

target_include_directories(${NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)
