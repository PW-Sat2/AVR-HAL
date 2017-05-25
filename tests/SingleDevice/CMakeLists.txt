cmake_minimum_required(VERSION 3.0)

set(NAME unit_tests)
set(BOARD ARDUINONANO328P)
set(CMAKE_TOOLCHAIN_FILE "../../toolchain.cmake")

project(${NAME})

add_subdirectory(unity)

add_subdirectory(../../ hal)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error" CACHE STRING "" FORCE)

add_hal_executable(${NAME}
        main.cpp
        tests/DigitalIO.cpp
        tests/SPI.cpp
        tests/ADC.cpp
        tests/I2C.cpp
)

include_directories(.)

target_link_libraries(${NAME}
    unity
    terminal
)
