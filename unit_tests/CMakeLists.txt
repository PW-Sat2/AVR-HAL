cmake_minimum_required(VERSION 3.0)

set(NAME unit_tests)
set(BOARD ARDUINOMEGA2560)
set(CMAKE_TOOLCHAIN_FILE "../toolchain.cmake")

project(${NAME})

add_subdirectory(unity)

add_subdirectory(../ hal)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error" CACHE STRING "" FORCE)

add_hal_executable(${NAME}
    main.cpp
    compile_time.cpp
    bit_operations.cpp
    array.cpp
    fifo.cpp
    ReaderTest.cpp
    WriterTest.cpp
    span.cpp
    I2C.cpp
    data_types.cpp
    eeprom.cpp
    terminal.cpp
    drivers/AD5641.cpp
)

include_directories(.)

target_link_libraries(${NAME}
    unity
    terminal
)
