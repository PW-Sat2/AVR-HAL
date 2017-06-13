set(NAME hal_std_addons)

add_library(${NAME} INTERFACE)

target_sources(${NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/array
    ${CMAKE_CURRENT_LIST_DIR}/initializer_list
    ${CMAKE_CURRENT_LIST_DIR}/tuple
)

target_include_directories(${NAME} INTERFACE .)
