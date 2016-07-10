#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

#include "libs/bit_operations.h"

#include "GPIOPinDescriptor.h"
#include "mcu/mcu.h"


namespace hal {
    
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
        io.pinmode(mode);
        return io;
    }
    
    constexpr DigitalIO(Pin pin) : pin(GPIOPinMap[pin].pin),
                                   DDRx(GPIOPinMap[pin].DDRx), 
                                   PORTx(GPIOPinMap[pin].PORTx), 
                                   PINx(GPIOPinMap[pin].PINx) {
    }
	
    void set() {
        SBI(*PORTx, pin);
    }

    void reset() {
        CBI(*PORTx, pin);
    }

    void write(bool value) {
	    if (value) {
		    this->set();
		} else {
		    this->reset();
	    }
    }
    
    bool read() {
	    if (bit_is_clear(*PINx, pin)) {
		    return false;
	    }
	    return true;
    }

    void pinmode(const DigitalIO::Mode mode) {
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
				
	    }
    }

 private:
    Pin pin;
    volatile uint8_t *DDRx, *PORTx, *PINx;
};
}

#endif  // HAL_GPIO_H_
