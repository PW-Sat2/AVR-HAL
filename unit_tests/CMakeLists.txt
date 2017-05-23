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

        periph/DigitalIO.cpp
        periph/eeprom.cpp

        libs/array.cpp
        libs/bit_operations.cpp
        libs/compile_time.cpp
        libs/data_types.cpp
        libs/fifo.cpp
        libs/ReaderTest.cpp
        libs/WriterTest.cpp
        libs/span.cpp
        libs/terminal.cpp

        drivers/AD5641.cpp
        drivers/ADG708.cpp
        drivers/ADG709.cpp
        drivers/LED.cpp
        drivers/devices_compilation.cpp

#    pure_virtual.cpp
)

include_directories(.)

target_link_libraries(${NAME}
    unity
    terminal
)
