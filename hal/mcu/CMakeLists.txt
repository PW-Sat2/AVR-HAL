set(NAME hal_mcu)
add_library(${NAME} INTERFACE)

file(GLOB_RECURSE HAL_MCU_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/${MCU_INCLUDE}/hal/*.h
)

target_sources(${NAME} INTERFACE ${HAL_MCU_SOURCES})

target_include_directories(${NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/${MCU_INCLUDE}
)
