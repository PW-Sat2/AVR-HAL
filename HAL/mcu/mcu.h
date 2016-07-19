
#ifdef MCU_ATMEGA2560_TQFP100
	#include "atmega2560_tqfp100/mcu_digitalIO.h"
	#include "atmega2560_tqfp100/mcu_serial.h"
	#include "atmega2560_tqfp100/mcu_spi.h"
#else
#ifdef MCU_ATMEGA328P_TQFP32
	#include "atmega328p_tqfp32/mcu_digitalIO.h"
	#include "atmega328p_tqfp32/mcu_serial.h"
	#include "atmega328p_tqfp32/mcu_spi.h"
#else
	#error "Incorrect or no MCU defined"
#endif
#endif
