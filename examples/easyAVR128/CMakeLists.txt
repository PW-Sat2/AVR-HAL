cmake_minimum_required(VERSION 3.0)
set(BOARD EASYAVR128)
set(CMAKE_TOOLCHAIN_FILE "../../toolchain.cmake")

project(examples_easyavr128)

add_subdirectory(../../ hal)

add_subdirectory(ADC-noise-reduction)
add_subdirectory(ClockPrescaler)
add_subdirectory(Timer0)
