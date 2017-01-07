#ifndef HAL_MCU_MCU_H_
#define HAL_MCU_MCU_H_

#if defined(MCU_ATMEGA2560_TQFP100)
    #include "atmega2560_tqfp100/mcu_digitalIO.h"
    #include "atmega2560_tqfp100/mcu_serial.h"
    #include "atmega2560_tqfp100/mcu_spi.h"
    #include "atmega2560_tqfp100/mcu_i2c.h"
    #include "atmega2560_tqfp100/mcu_analog.h"
    #include "atmega2560_tqfp100/mcu_watchdog.h"
#elif defined(MCU_ATMEGA328P_TQFP32)
    #include "atmega328p_tqfp32/mcu_digitalIO.h"
    #include "atmega328p_tqfp32/mcu_serial.h"
    #include "atmega328p_tqfp32/mcu_spi.h"
    #include "atmega328p_tqfp32/mcu_i2c.h"
    #include "atmega328p_tqfp32/mcu_analog.h"
    #include "atmega328p_tqfp32/mcu_watchdog.h"
#elif defined(MCU_ATMEGA164P_324P_644P_44)
    #include "atmega164p_324p_644p_44/mcu_digitalIO.h"
    #include "atmega164p_324p_644p_44/mcu_serial.h"
    #include "atmega164p_324p_644p_44/mcu_spi.h"
    #include "atmega164p_324p_644p_44/mcu_i2c.h"
    #include "atmega164p_324p_644p_44/mcu_analog.h"
    #include "atmega164p_324p_644p_44/mcu_watchdog.h"
#elif defined(MCU_ATMEGA128A_TQFP64)
    #include "atmega128a_tqfp64/mcu_digitalIO.h"
    #include "atmega128a_tqfp64/mcu_serial.h"
    #include "atmega128a_tqfp64/mcu_analog.h"
    #include "atmega128a_tqfp64/mcu_core.h"
    #include "atmega128a_tqfp64/mcu_timers.h"
    #include "atmega128a_tqfp64/mcu_watchdog.h"
    #include "atmega128a_tqfp64/mcu_spi.h"
    #include "atmega128a_tqfp64/mcu_exti.h"
    #include "atmega128a_tqfp64/mcu_i2c.h"
#elif defined(MCU_ATMEGA644P_DIP40)
    #include "atmega644p_dip40/mcu_digitalIO.h"
    #include "atmega644p_dip40/mcu_serial.h"
    #include "atmega644p_dip40/mcu_analog.h"
    #include "atmega644p_dip40/mcu_watchdog.h"
    #include "atmega644p_dip40/mcu_spi.h"
    #include "atmega644p_dip40/mcu_i2c.h"
#else
#error "Incorrect or no MCU defined"
#endif

#endif  // HAL_MCU_MCU_H_
