cmake_minimum_required(VERSION 3.0)

set(BOARD ARDUINOMEGA2560)
set(CMAKE_TOOLCHAIN_FILE "../toolchain.cmake")

project(unit_tests)

add_subdirectory(unity)

add_subdirectory(../ hal)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error" CACHE STRING "" FORCE)

add_hal_executable(unit_tests
        main.cpp

        periph/DigitalIO.cpp
        periph/eeprom.cpp
        periph/SPIHardware.cpp

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
        drivers/ADC12x.cpp
        drivers/LED.cpp
        drivers/devices_compilation.cpp

#    pure_virtual.cpp
)

add_custom_target(unit_tests.run
    COMMAND ${SIMULAVR} -d ${SIMULAVR_TARGET} -f unit_tests.elf -W 0xC6,- -R 0x22,- -T exit | tee ${CMAKE_BINARY_DIR}/unit_tests.output
    COMMAND grep "FAIL" ${CMAKE_BINARY_DIR}/unit_tests.output && exit 1; || exit 0;
    DEPENDS unit_tests
)

include_directories(.)

target_link_libraries(unit_tests
    unity
    terminal
)
