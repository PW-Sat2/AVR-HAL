set(NAME hal_std_addons)

add_library(${NAME} STATIC
    array
    initializer_list
    tuple
)

target_include_directories(${NAME} PUBLIC .)

target_link_libraries(${NAME} hal)
