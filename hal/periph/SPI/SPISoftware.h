#ifndef HAL_PERIPH_SPI_SPISOFTWARE_H_
#define HAL_PERIPH_SPI_SPISOFTWARE_H_

#include <avr/io.h>
#include <util/delay.h>
#include "SPI.h"

#include "hal/periph/GPIO/DigitalIO.h"
#include "hal/mcu.h"
#include "hal/libs.h"

namespace hal {
namespace SPI {

template<SPI::Polarity polarity,
         SPI::Phase phase>
class Software : public ISPI {
 public:
    Software(IDigitalIO& pin_mosi,
             IDigitalIO& pin_miso,
             IDigitalIO& pin_sck) : pin_mosi{pin_mosi},
                                    pin_miso{pin_miso},
                                    pin_sck{pin_sck} {}

    void init() {
        pin_miso.init(IDigitalIO::Mode::INPUT_PULLUP);
        pin_mosi.init(IDigitalIO::Mode::OUTPUT);
        pin_sck.init(IDigitalIO::Mode::OUTPUT);

        if (polarity == SPI::Polarity::idle_high) {
            pin_sck.set();
        } else {
            pin_sck.reset();
        }
    }

    void disable() {
        pin_miso.init(IDigitalIO::Mode::INPUT);
        pin_mosi.init(IDigitalIO::Mode::INPUT);
        pin_sck.init(IDigitalIO::Mode::INPUT);
    }

    uint8_t shift(const uint8_t data) {
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
    IDigitalIO& pin_mosi;
    IDigitalIO& pin_miso;
    IDigitalIO& pin_sck;

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

#endif  // HAL_PERIPH_SPI_SPISOFTWARE_H_
