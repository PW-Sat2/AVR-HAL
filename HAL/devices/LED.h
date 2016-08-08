#ifndef HAL_DEVICES_LED_H_
#define HAL_DEVICES_LED_H_

namespace hal {
class LED {
 public:
    constexpr LED(const DigitalIO::Pin pin) :
            led_output_pin(pin) {
    }

    void init() const {
        led_output_pin.pinmode(DigitalIO::OUTPUT);
    }

    void on() const {
        led_output_pin.set();
    }

    void off() const {
        led_output_pin.reset();
    }

    void write(bool state) const {
        led_output_pin.write(state);
    }

    void toggle() const {
        led_output_pin.toggle();
    }

 private:
    const DigitalIO led_output_pin;
};

}  // namespace hal

#endif  // HAL_DEVICES_LED_H_
