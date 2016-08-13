#ifndef HAL_MCU_MCU_H_
#define HAL_MCU_MCU_H_

#ifdef MCU_ATMEGA2560_TQFP100
#include "atmega2560_tqfp100/mcu_digitalIO.h"
#include "atmega2560_tqfp100/mcu_serial.h"
#include "atmega2560_tqfp100/mcu_spi.h"
#include "atmega2560_tqfp100/mcu_i2c.h"
#include "atmega2560_tqfp100/mcu_analog.h"
#include "atmega2560_tqfp100/mcu_watchdog.h"
#else
#ifdef MCU_ATMEGA328P_TQFP32
#include "atmega328p_tqfp32/mcu_digitalIO.h"
#include "atmega328p_tqfp32/mcu_serial.h"
#include "atmega328p_tqfp32/mcu_spi.h"
#include "atmega328p_tqfp32/mcu_i2c.h"
#include "atmega328p_tqfp32/mcu_analog.h"
#include "atmega328p_tqfp32/mcu_watchdog.h"
#else
#ifdef MCU_ATMEGA128A_TQFP64
#include "atmega128a_tqfp64/mcu_digitalIO.h"
#include "atmega128a_tqfp64/mcu_serial.h"
#include "atmega128a_tqfp64/mcu_analog.h"
#include "atmega128a_tqfp64/mcu_core.h"
#include "atmega128a_tqfp64/mcu_timers.h"
#include "atmega128a_tqfp64/mcu_watchdog.h"
#include "atmega128a_tqfp64/mcu_spi.h"
#include "atmega128a_tqfp64/mcu_exti.h"
#include "atmega128a_tqfp64/mcu_i2c.h"
#else
#error "Incorrect or no MCU defined"
#endif
#endif
#endif

#endif  // HAL_MCU_MCU_H_
