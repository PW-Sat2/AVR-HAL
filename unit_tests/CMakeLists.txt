cmake_minimum_required(VERSION 3.5)

set(NAME unit_tests)
project(${NAME} C CXX)
add_subdirectory(gtest)

set(CMAKE_CXX_FLAGS "-std=c++1y")

add_subdirectory(../HAL hal)
add_subdirectory(board)

add_executable(${NAME}
    array.cpp
    bit_operations.cpp
    compile_time.cpp
    fifo.cpp
    I2C.cpp
    span.cpp
    ReaderTest.cpp
    WriterTest.cpp
)



target_link_libraries(${NAME}
    hal
    libs
    gtest
    gtest_main
)

add_custom_target(unit_tests.run
  ${CMAKE_CURRENT_BINARY_DIR}/unit_tests
  DEPENDS ${NAME}
)