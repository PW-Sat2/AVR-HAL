cmake_minimum_required(VERSION 3.2)

# Download and unpack gsl-lite at configure time
configure_file(CMakeLists.txt.in ${CMAKE_CURRENT_BINARY_DIR}/gsl/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM} -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gsl
)

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gsl
)

add_library(gsl INTERFACE)

target_include_directories(gsl INTERFACE
    ${CMAKE_CURRENT_BINARY_DIR}/gsl-src/include
)
