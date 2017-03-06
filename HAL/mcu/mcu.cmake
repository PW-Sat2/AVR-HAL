SET(       includes_AT90CAN128_TQFP64    at90can128_tqfp64)
SET(     GCC_TARGET_AT90CAN128_TQFP64    at90can128)
SET( AVRDUDE_TARGET_AT90CAN128_TQFP64    at90can128)

SET(       includes_ATMEGA128A_TQFP64    atmega128a_tqfp64)
SET(     GCC_TARGET_ATMEGA128A_TQFP64    atmega128a)
SET( AVRDUDE_TARGET_ATMEGA128A_TQFP64    m128)

SET(           includes_ATMEGA164A_44    atmega164p_324p_644p_44)
SET(         GCC_TARGET_ATMEGA164P_44    atmega164a)
SET(     AVRDUDE_TARGET_ATMEGA164P_44    m164pa)

SET(           includes_ATMEGA164P_44    atmega164p_324p_644p_44)
SET(         GCC_TARGET_ATMEGA164P_44    atmega164p)
SET(     AVRDUDE_TARGET_ATMEGA164P_44    m164p)

SET(           includes_ATMEGA324P_44    atmega164p_324p_644p_44)
SET(         GCC_TARGET_ATMEGA324P_44    atmega324p)
SET(     AVRDUDE_TARGET_ATMEGA324P_44    m324p)

SET(           includes_ATMEGA324A_44    atmega164p_324p_644p_44)
SET(         GCC_TARGET_ATMEGA324A_44    atmega324a)
SET(     AVRDUDE_TARGET_ATMEGA324A_44    m324pa)

SET(           includes_ATMEGA644P_44    atmega164p_324p_644p_44)
SET(         GCC_TARGET_ATMEGA644P_44    atmega664p)
SET(     AVRDUDE_TARGET_ATMEGA644P_44    m664p)

SET(           includes_ATMEGA644A_44    atmega164p_324p_644p_44)
SET(         GCC_TARGET_ATMEGA644P_44    atmega664a)
SET(     AVRDUDE_TARGET_ATMEGA644P_44    m664pa)

SET(       includes_ATMEGA328P_TQFP32    atmega328p_tqfp32)
SET(     GCC_TARGET_ATMEGA328P_TQFP32    atmega328p)
SET( AVRDUDE_TARGET_ATMEGA328P_TQFP32    m328p)

SET(        includes_ATMEGA644P_DIP40    atmega644p_dip40)
SET(      GCC_TARGET_ATMEGA644P_DIP40    atmega644p)
SET(  AVRDUDE_TARGET_ATMEGA644P_DIP40    m644p)

SET(      includes_ATMEGA2560_TQFP100    atmega2560_tqfp100)
SET(    GCC_TARGET_ATMEGA2560_TQFP100    atmega2560)
SET(AVRDUDE_TARGET_ATMEGA2560_TQFP100    atmega2560)

if(includes_${HAL_MCU})
else()
    message(FATAL_ERROR "Incorrect MCU defined! HAL_MCU=${HAL_MCU}")
endif(includes_${HAL_MCU})

set(include ${includes_${HAL_MCU}})
set(GCC_TARGET ${GCC_TARGET_${HAL_MCU}} CACHE STRING "gcc target passed to -mmcu flag")
set(AVRDUDE_TARGET ${AVRDUDE_TARGET_${HAL_MCU}} CACHE STRING "avrdude target passed to -p flag")

message(STATUS "HAL_MCU: ${HAL_MCU}")
message(STATUS "GCC_TARGET: ${GCC_TARGET}")
message(STATUS "AVRDUDE_TARGET: ${AVRDUDE_TARGET}")
message(STATUS "MCU include: ${include}")