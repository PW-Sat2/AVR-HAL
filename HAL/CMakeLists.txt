set(NAME hal)
add_library(${NAME} INTERFACE)

add_subdirectory(boards)
add_subdirectory(mcu)


target_link_libraries(${NAME} INTERFACE board mcu)

target_include_directories(${NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/periph
    ${CMAKE_CURRENT_LIST_DIR}/libs
    ${CMAKE_CURRENT_LIST_DIR}/devices
)