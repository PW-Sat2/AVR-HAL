set(NAME hal_libs)

add_subdirectory(terminal)

add_library(${NAME} STATIC
    reader.cpp
    reader.h
    writer.cpp
    writer.h

    bit_operations.h
    compile_time.h
    fifo.h
    simavr.h
)

target_include_directories(${NAME} PUBLIC
    ../../
)

add_subdirectory(base)
add_subdirectory(gsl)
add_subdirectory(gcc_addons)

target_link_libraries(${NAME} terminal hal_gcc_addons gsl)
