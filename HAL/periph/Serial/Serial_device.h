#ifndef	HAL_PERIPH_SERIAL_DEVICE_H_
#define	HAL_PERIPH_SERIAL_DEVICE_H_

#include <avr/io.h>
#include "Serial_defines.h"

extern bool serial_wrong_number;

#define SERIAL_REG(reg_p, reg_s) \
template<int uart_nr>                \
volatile uint8_t& reg_p ## n ## reg_s() { \
    return serial_wrong_number; \
}

SERIAL_REG(UBRR, H);
SERIAL_REG(UBRR, L);
SERIAL_REG(UCSR, A);
SERIAL_REG(UCSR, B);
SERIAL_REG(UCSR, C);
SERIAL_REG(UDR ,  );

#undef SERIAL_REG

#define SERIAL_MAKE_REG(reg_p, reg_s, nr) \
template<>                                \
volatile uint8_t& reg_p ## n ## reg_s  \
<nr>() {  \
    return reg_p ## nr ## reg_s; \
}

#define SERIAL_DEF(nr)  SERIAL_MAKE_REG(UBRR, H, nr);    \
                        SERIAL_MAKE_REG(UBRR, L, nr);    \
                        SERIAL_MAKE_REG(UCSR, A, nr);    \
                        SERIAL_MAKE_REG(UCSR, B, nr);    \
                        SERIAL_MAKE_REG(UCSR, C, nr);    \
                        SERIAL_MAKE_REG(UDR ,  , nr);


#if defined(UBRR3H)
    #define MCU_NR_OF_SERIALS 4
    SERIAL_DEF(0);
    SERIAL_DEF(1);
    SERIAL_DEF(2);
    SERIAL_DEF(3);
#elif defined(UBRR1H)
    #define MCU_NR_OF_SERIALS 2
    SERIAL_DEF(0);
    SERIAL_DEF(1);
#else
    #define MCU_NR_OF_SERIALS 1
    SERIAL_DEF(0);
#endif

#undef SERIAL_MAKE_REG
#undef SERIAL_DEF

#endif	// HAL_PERIPH_SERIAL_DEVICE_H_
