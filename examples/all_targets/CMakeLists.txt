cmake_minimum_required(VERSION 3.0)

set(CMAKE_TOOLCHAIN_FILE "../../toolchain.cmake")

project(examples_all_targets)

add_subdirectory(../../ hal)


add_subdirectory(ADC)
add_subdirectory(ADXRS453)
add_subdirectory(AT24C02_SoftI2C)
add_subdirectory(AT24C02_TWI)
add_subdirectory(bsp)
add_subdirectory(DigitalIO)
add_subdirectory(EEPROM)
add_subdirectory(EXTI)
add_subdirectory(PCF8563)
add_subdirectory(Serial)
add_subdirectory(Serial-rx-interrupt)
add_subdirectory(Serial-stdio)
add_subdirectory(SoftI2C)
add_subdirectory(SPI)
add_subdirectory(TWI)
add_subdirectory(TWISlave)
add_subdirectory(Watchdog)
add_subdirectory(TPS3813)
add_subdirectory(ADG849)
