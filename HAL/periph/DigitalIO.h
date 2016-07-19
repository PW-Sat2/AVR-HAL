#ifndef HAL_PERIPH_DIGITALIO_H_
#define HAL_PERIPH_DIGITALIO_H_

#include "PeriphDescriptors.h"
#include "bit_operations.h"

#include "mcu.h"


namespace hal {

// hack for checking bad pin association
extern int DigitalIO_bad_pin_or_cannot_be_evaluated_at_compile_time;

class DigitalIO { 
 public:
	typedef uint8_t Pin;
    enum Mode {
        INPUT,
        OUTPUT,
        INPUT_PULLUP
    };

    constexpr explicit DigitalIO(Pin pin) : pin(mcu::DigitalIOPinMap[pin].pin),
                                   DDRx((mcu::DigitalIOPinMap[pin].DDRx == 0 ) ? DigitalIO_bad_pin_or_cannot_be_evaluated_at_compile_time : mcu::DigitalIOPinMap[pin].DDRx),
                                   PORTx(mcu::DigitalIOPinMap[pin].PORTx),
                                   PINx(mcu::DigitalIOPinMap[pin].PINx) {
    }
	
	void init(const DigitalIO::Mode mode) const __attribute__((always_inline)) {
		pinmode(mode);
	}
	
    void set() const __attribute__((always_inline)) {
        set_bit(PORTx);
    }

    void reset() const __attribute__((always_inline)) {
       clear_bit(PORTx);
    }

    void write(bool value) const __attribute__((always_inline)) {
	    if (value) {
		    this->set();
		} else {
		    this->reset();
	    }
    }
    
    bool read() const __attribute__((always_inline)) {
	    if (bit_is_clear(*((volatile uint8_t *)(PINx)), pin)) {
		    return false;
	    }
	    return true;
    }
	
	void toggle() const __attribute__((always_inline)) {
		if( read() ) {
			reset();
		} else {
			set();
		}	
	}

    inline void pinmode(const DigitalIO::Mode mode) const __attribute__((always_inline)) {
		switch(mode) {
			case OUTPUT:
                set_bit(DDRx);
                clear_bit(PORTx);
				break;
			case INPUT_PULLUP:
                clear_bit(DDRx);
                set_bit(PORTx);
				break;
			case INPUT:
			default:
                clear_bit(DDRx);
                clear_bit(PORTx);
				break;
	    }
    }
    
 private:
    const Pin pin;
    const int DDRx, PORTx, PINx;
    
    void set_bit(int reg) const __attribute__((always_inline)) {
        SBI(*((volatile uint8_t *)(reg)), pin);
    }
    
    void clear_bit(int reg) const __attribute__((always_inline)) {
        CBI(*((volatile uint8_t *)(reg)), pin);
    }
};
}


#endif  // HAL_PERIPH_DIGITALIO_H_
