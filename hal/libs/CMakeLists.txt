set(NAME hal_libs)

add_subdirectory(terminal)

add_library(${NAME} STATIC
    reader.cpp
    writer.cpp
)

target_include_directories(${NAME} PUBLIC
    ../../
)

if(ENABLE_HAL_STD)
    message(STATUS "Using hal std library")

    add_subdirectory(std)
    add_subdirectory(gcc_addons)
    add_subdirectory(std_addons)
    add_subdirectory(gsl)
    target_link_libraries(${NAME} hal_stdlib hal_gcc_addons hal_std_addons gsl)
endif(ENABLE_HAL_STD)