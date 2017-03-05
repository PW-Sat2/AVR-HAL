# find the toolchain root directory
INCLUDE(CMakeForceCompiler)

set(CMAKE_SYSTEM_NAME Generic)

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

CMAKE_FORCE_C_COMPILER(${CC} GNU)
CMAKE_FORCE_CXX_COMPILER(${CXX} GNU)

message(STATUS "Using HAL from ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "Using C compiler from ${CMAKE_C_COMPILER}")

# setup the avr exectable macro

set(AVR_LINKER_LIBS "-lc -lm -lgcc")


macro(add_hal_executable target_name)
	set(AVR_MCU ${GCC_TARGET})
	set(elf_file ${target_name})
	set(map_file ${target_name}-${AVR_MCU}.map)
	set(hex_file ${target_name}-${AVR_MCU}.hex)
	set(lst_file ${target_name}-${AVR_MCU}.lst)

	# create elf file
	add_executable(${elf_file}
		${ARGN}
	)
	target_link_libraries(${elf_file} hal)

	if(F_CPU)
		add_definitions("-DF_CPU=${F_CPU}L")
		message(STATUS "MCU core frequency = ${F_CPU}")
	else()
		message(WARNING "No MCU core frequency defined!")
	endif(F_CPU)

	set (CWARN "-Wall -Wstrict-prototypes -Wextra -Werror")
	set (CXXWARN "-Wall -Wextra -Werror")
	set (CTUNING "-DNDEBUG -O2 -g -ggdb -pedantic -fomit-frame-pointer -ffunction-sections -fdata-sections")
	set (CMCU "-mmcu=${AVR_MCU}")
	set (CMAKE_C_FLAGS "-std=gnu11 ${CWARN} ${CTUNING} ${CMCU}")
	set (CMAKE_CXX_FLAGS "-std=gnu++1y -fno-exceptions ${CXXWARN} ${CTUNING} ${CMCU}")
	set (CMAKE_CXX_STANDARD 14)

	set_target_properties(
		${elf_file}
		PROPERTIES
			LINK_FLAGS    "-mmcu=${AVR_MCU} -Wl,-Map,${map_file} ${AVR_LINKER_LIBS}"
	)

	# generate the lst file
	add_custom_command(
		OUTPUT ${lst_file}
		COMMAND
			${CMAKE_OBJDUMP} -h -S ${elf_file} > ${lst_file}
		DEPENDS ${elf_file}
	)

	# create hex file
	add_custom_command(
		OUTPUT ${hex_file}
		COMMAND
			${CMAKE_OBJCOPY} -j .text -j .data -O ihex ${elf_file} ${hex_file}
		DEPENDS ${elf_file}
	)
	add_custom_command(
		OUTPUT "print-size-${elf_file}"
		COMMAND
			${CMAKE_GCC_SIZE} ${elf_file}
		DEPENDS ${elf_file}
	)

	# build the intel hex file for the device
	add_custom_target(
		${target_name}.build
		ALL
		DEPENDS ${hex_file} ${lst_file} "print-size-${elf_file}"
	)
	set_target_properties(
		${target_name}.build
		PROPERTIES
			OUTPUT_NAME ${elf_file}
	)


	# flash command
	message(STATUS "Avrdude parameters: -c${AVRDUDE_TOOL} -p${AVRDUDE_TARGET} ${AVRDUDE_OPTIONS}")

	set(AVRDUDE_ARGS -c${AVRDUDE_TOOL} -p${AVRDUDE_TARGET} ${AVRDUDE_OPTIONS} -U flash:w:${hex_file})
	message(STATUS "Command: ${AVRDUDE_ARGS}")

	add_custom_command(
		OUTPUT "flash-${hex_file}"
		COMMAND
			${AVRDUDE} ${AVRDUDE_ARGS}
	)
	add_custom_target(
		"${target_name}-flash"
		DEPENDS ${hex_file} "flash-${hex_file}"
	)

endmacro(add_hal_executable)
