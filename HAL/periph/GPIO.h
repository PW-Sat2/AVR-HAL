#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

#include "libs/bit_operations.h"

#include "GPIOPinDescriptor.h"
#include "mcu/mcu.h"




namespace hal {

// hack for checking bad pin association
extern volatile uint8_t* DigitalIO_bad_pin;

class DigitalIO { 
 public:
	typedef uint8_t Pin;
    enum Mode {
        INPUT,
        OUTPUT,
        INPUT_PULLUP
    };
    
    template<Pin pin_nr, Mode mode>
    static DigitalIO init() {
        DigitalIO io = DigitalIO(pin_nr);
        static_assert(reinterpret_cast<int>(GPIOPinMap[pin_nr].DDRx) != 0, "Pin is not GPIO!");
        io.init(mode);
        return io;
    }			
    
    
    constexpr DigitalIO(Pin pin) : pin(GPIOPinMap[pin].pin),
                                   DDRx((GPIOPinMap[pin].DDRx == 0 ) ? DigitalIO_bad_pin : GPIOPinMap[pin].DDRx),
                                   PORTx(GPIOPinMap[pin].DDRx),
                                   PINx(GPIOPinMap[pin].DDRx) {
    }
	
	void init(const DigitalIO::Mode mode) __attribute__((always_inline)) {
		pinmode(mode);
	}
	
    void set() __attribute__((always_inline)) {
        SBI(*PORTx, pin);
    }

    void reset() __attribute__((always_inline)) {
        CBI(*PORTx, pin);
    }

    void write(bool value) __attribute__((always_inline)) {
	    if (value) {
		    this->set();
		} else {
		    this->reset();
	    }
    }
    
    bool read() __attribute__((always_inline)) {
	    if (bit_is_clear(*PINx, pin)) {
		    return false;
	    }
	    return true;
    }
	
	void toggle() __attribute__((always_inline)) {
		if( read() ) {
			reset();
		} else {
			set();
		}	
	}

    inline void pinmode(const DigitalIO::Mode mode) __attribute__((always_inline)) {
		switch(mode) {
			case OUTPUT:
                SBI(*DDRx, pin);
                CBI(*PORTx, pin);
				break;
			case INPUT_PULLUP:
				CBI(*DDRx, pin);
				SBI(*PORTx, pin);
				break;
			case INPUT:
			default:
			    CBI(*DDRx, pin);
			    CBI(*PORTx, pin);
				break;
	    }
    }

 private:
    const Pin pin;
    volatile uint8_t * const DDRx;
	volatile uint8_t * const PORTx;
	volatile uint8_t * const PINx;
};
}


#endif  // HAL_GPIO_H_
