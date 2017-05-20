#ifndef HAL_PERIPH_SPI_SOFTWARE_H_
#define HAL_PERIPH_SPI_SOFTWARE_H_

#include <avr/io.h>
#include <util/delay.h>

#include "hal/periph/DigitalIO/Interface.h"
#include "hal/mcu.h"
#include "hal/libs.h"

#include "Interface.h"

namespace hal {
namespace SPI {

template<hal::DigitalIO::Interface::Pin pin_chip_select,
         SPI::Polarity polarity,
         SPI::Phase phase>
class Software : public details::BlockTransfer<pin_chip_select> {
 public:
    Software(DigitalIO::Interface& pin_mosi,
             DigitalIO::Interface& pin_miso,
             DigitalIO::Interface& pin_sck) : pin_mosi{pin_mosi},
                                    pin_miso{pin_miso},
                                    pin_sck{pin_sck} {}

    void init() {
        pin_miso.init(DigitalIO::Interface::Mode::INPUT_PULLUP);
        pin_mosi.init(DigitalIO::Interface::Mode::OUTPUT);
        pin_sck.init(DigitalIO::Interface::Mode::OUTPUT);

        if (polarity == SPI::Polarity::idle_high) {
            pin_sck.set();
        } else {
            pin_sck.reset();
        }
    }

    void disable() {
        pin_miso.init(DigitalIO::Interface::Mode::INPUT);
        pin_mosi.init(DigitalIO::Interface::Mode::INPUT);
        pin_sck.init(DigitalIO::Interface::Mode::INPUT);
    }

    uint8_t transfer(const uint8_t data) override {
        if (phase == SPI::Phase::leading_sample) {
            return shift_leading_sample(data);
        } else {
            return shift_trailing_sample(data);
        }
    }

    uint8_t shift_trailing_sample(const uint8_t data) {
        uint8_t output = 0;
        delay();
        for (int8_t i = 7; i >= 0; --i) {
            output_phase(data & (1u << i));
            pin_sck.toggle();
            delay();
            output |= (sample_phase() << i);
            pin_sck.toggle();
            delay();
        }
        return output;
    }

    uint8_t shift_leading_sample(const uint8_t data) {
        uint8_t output = 0;
        delay();
        for (int8_t i = 7; i >= 0; --i) {
            output_phase(data & (1u << i));
            delay();
            output |= (sample_phase() << i);
            pin_sck.toggle();
            delay();
            pin_sck.toggle();
        }
        return output;
    }

 private:
    DigitalIO::Interface& pin_mosi;
    DigitalIO::Interface& pin_miso;
    DigitalIO::Interface& pin_sck;

    bool sample_phase() {
        return pin_miso.read();
    }

    void output_phase(bool value) {
        pin_mosi.write(value);
    }

    void delay() {
        _delay_us(10);
    }
};

}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPI_SOFTWARE_H_
