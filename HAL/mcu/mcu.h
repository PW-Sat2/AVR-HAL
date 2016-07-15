#ifdef MCU_ATMEGA2560_TQFP100
	#include "atmega2560_tqfp100/atmega2560_tqfp100.h"
#else
#ifdef MCU_ATMEGA328P_TQFP32
	#include "atmega328p_tqfp32/atmega328p_tqfp32.h"
#else
	#error "Incorrect or no MCU defined"
#endif
#endif
