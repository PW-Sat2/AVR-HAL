#ifndef HAL_LED_H_
#define HAL_LED_H_

namespace hal {
class LED {
 public:
    constexpr LED(const DigitalIO::Pin pin) : led_pin(pin) {	 
    }
    void init() {
        led_pin.pinmode(DigitalIO::OUTPUT);
    }
	
	void on() {
		led_pin.set();
	}
	
	void off() {
		led_pin.reset();
	}
	
	void write(bool state) {
		led_pin.write(state);
	}
 private:
	DigitalIO led_pin;
};
}

#endif  // HAL_LED_H_
