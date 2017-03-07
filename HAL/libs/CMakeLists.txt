set(NAME libs)

add_library(${NAME} STATIC
    reader.cpp
    writer.cpp
)

if(ENABLE_HAL_STD)
    add_subdirectory(std)
    message(STATUS "Using hal std library")
    target_link_libraries(${NAME} stdlib)
    #target_include_directories(${NAME} INTERFACE stdlib)
endif(ENABLE_HAL_STD)

target_include_directories(${NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/device_supports
)
