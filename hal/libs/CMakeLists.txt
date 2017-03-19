set(NAME libs)

add_subdirectory(terminal)

add_library(${NAME} STATIC
    reader.cpp
    writer.cpp
)

if(ENABLE_HAL_STD)
    message(STATUS "Using hal std library")

    add_subdirectory(std)
    add_subdirectory(gcc_addons)
    target_link_libraries(${NAME} stdlib gcc_addons)
endif(ENABLE_HAL_STD)

target_include_directories(${NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/device_supports
)
