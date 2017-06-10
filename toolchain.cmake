# find the toolchain root directory
INCLUDE(CMakeForceCompiler)

set(CMAKE_SYSTEM_NAME Generic)

# resolve board -> mcu if board from HAL
include(${CMAKE_CURRENT_LIST_DIR}/hal/boards/board.cmake)
# resolve mcu -> build variables
include(${CMAKE_CURRENT_LIST_DIR}/hal/mcu/mcu.cmake)

find_program(CC NAMES avr-gcc)
find_program(CXX NAMES avr-g++)

find_program(CMAKE_GCOV NAMES avr-gcov)
find_program(CMAKE_AR NAMES avr-gcc-ar)
find_program(CMAKE_RANLIB NAMES avr-gcc-ranlib)
find_program(CMAKE_OBJCOPY NAMES avr-objcopy)
find_program(CMAKE_OBJDUMP NAMES avr-objdump)
find_program(CMAKE_GCC_SIZE NAMES avr-size)
find_program(GDB NAMES avr-gdb-py)
find_program(CMAKE_MAKE_PROGRAM NAMES make)

find_program(AVRDUDE NAMES avrdude)
find_program(PICOCOM NAMES picocom)

find_program(SIMULAVR NAMES simulavr)

CMAKE_FORCE_C_COMPILER(${CC} GNU)
CMAKE_FORCE_CXX_COMPILER(${CXX} GNU)

message(STATUS "Using HAL from ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "Using C compiler from ${CMAKE_C_COMPILER}")
message(STATUS "SimulAVR: ${SIMULAVR}")
message(STATUS "PicoCOM: ${PICOCOM}")

set(AVR_LINKER_LIBS "-lc -lm -lgcc")

set(ENABLE_HAL_STD TRUE)

set (CWARN "-Wall -Wstrict-prototypes -Wextra -Werror")
set (CXXWARN "-Wall -Wextra -Werror")
set (CTUNING "-Os -fomit-frame-pointer -ffunction-sections -fdata-sections -flto")
set (CWORKAROUNDS "-Wno-format")
set (CMCU "-mmcu=${GCC_TARGET} -DF_CPU=${F_CPU}L")

set (CMAKE_C_FLAGS "-std=gnu11 ${CMCU} ${CWARN} ${CTUNING} ${CWORKAROUNDS}" CACHE STRING "" FORCE)
set (CMAKE_CXX_FLAGS "-std=gnu++1y ${CMCU} -fno-exceptions ${CXXWARN} ${CTUNING} ${CWORKAROUNDS}" CACHE STRING "" FORCE)

set (TERMINAL_PORT "" CACHE STRING "Port for terminal operations")
set (TERMINAL_BAUD "" CACHE STRING "Baudrate for terminal operations")
set (TERMINAL_PICOCOM_OPTIONS -l --imap lfcrlf --omap crlf CACHE STRING "Options for picocom")

macro(add_hal_executable target_name)
	set(target ${target_name})
	set(elf_file ${target_name}.elf)
	set(map_file ${target_name}.map)
	set(hex_file ${target_name}.hex)
	set(lst_file ${target_name}.lst)

	# create elf file
	add_executable(${target}
		${ARGN}
	)
	target_link_libraries(${target} hal)
	set_target_properties(${target} PROPERTIES OUTPUT_NAME ${elf_file})

	set_target_properties(
		${target}
		PROPERTIES
			LINK_FLAGS "-mmcu=${GCC_TARGET} -Wl,-Map,${map_file} -Wl,-u,vfprintf -lprintf_flt -lm ${AVR_LINKER_LIBS} -flto"
	)

	# generate the lst file
	add_custom_command(
		OUTPUT ${lst_file}
		COMMAND
			${CMAKE_OBJDUMP} -h -S ${elf_file} > ${lst_file}
		DEPENDS ${target}
	)

	# create hex file
	add_custom_command(
		OUTPUT ${hex_file}
		COMMAND
			${CMAKE_OBJCOPY} -j .text -j .data -O ihex ${elf_file} ${hex_file}
		DEPENDS ${target}
	)
	add_custom_command(
		OUTPUT "print-size-${target}"
		COMMAND
			${CMAKE_GCC_SIZE} ${elf_file}
		DEPENDS ${target}
	)

	# build the intel hex file for the device
	add_custom_target(
		${target_name}.build
		ALL
		DEPENDS ${hex_file} ${lst_file} "print-size-${target}"
	)
	set_target_properties(
		${target_name}.build
		PROPERTIES
			OUTPUT_NAME ${target}
	)

	# flash command
	add_custom_command(
		OUTPUT "${hex_file}.flash"
		COMMAND
			${AVRDUDE} -c${AVRDUDE_TOOL} -p${AVRDUDE_TARGET} ${AVRDUDE_OPTIONS} -U flash:w:${hex_file}
	)
	add_custom_target(
		"${target_name}.flash"
		DEPENDS ${target_name}.build "${hex_file}.flash"
	)

	add_custom_target(${target_name}.sim
		COMMAND ${SIMULAVR} -d ${SIMULAVR_TARGET} -f ${elf_file} -W 0xC6,- -R 0x22,- -T exit
		DEPENDS ${target_name}.build
	)

	add_custom_command(
		OUTPUT "${target_name}.term_"
		COMMAND
			${PICOCOM} ${TERMINAL_PORT} -b${TERMINAL_BAUD} ${TERMINAL_PICOCOM_OPTIONS}
	)

	# terminal handling
	add_custom_command(
		OUTPUT "${target_name}.term_"
		COMMAND
			${PICOCOM} ${TERMINAL_PORT} -b${TERMINAL_BAUD} ${TERMINAL_PICOCOM_OPTIONS}
	)

	add_custom_target(
		"${target_name}.term"
		DEPENDS "${target_name}.term_"
	)

	add_custom_target(
		"${target_name}.flash_and_term"
		DEPENDS "${target_name}.build" "${hex_file}.flash" "${target_name}.term_"
	)
endmacro(add_hal_executable)

if(NOT TARGET term)
	add_custom_command(
		OUTPUT "term_"
		COMMAND
			${PICOCOM} ${TERMINAL_PORT} -b${TERMINAL_BAUD} ${TERMINAL_PICOCOM_OPTIONS}
	)

	add_custom_target(
		"term"
		DEPENDS "term_"
	)
endif(NOT TARGET term)