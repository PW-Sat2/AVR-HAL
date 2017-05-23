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

    array.cpp
    bit_operations.cpp
    compile_time.cpp
    data_types.cpp
    DigitalIO.cpp
    fifo.cpp
    ReaderTest.cpp
    WriterTest.cpp
    span.cpp
    eeprom.cpp
    terminal.cpp
    drivers/AD5641.cpp
    drivers/ADG708.cpp
    drivers/ADG709.cpp
    drivers/LED.cpp

    devices_compilation.cpp

#    pure_virtual.cpp
)

include_directories(.)

target_link_libraries(${NAME}
    unity
    terminal
)
