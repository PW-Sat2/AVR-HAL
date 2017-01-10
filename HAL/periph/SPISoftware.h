#ifndef HAL_PERIPH_SPISOFT__H_
#define HAL_PERIPH_SPISOFT__H_

#include <avr/io.h>
#include <util/delay.h>
#include "SPI.h"

#include "mcu.h"
#include "bit_operations.h"
#include "DigitalIO.h"
#include "array.h"

namespace hal {
namespace SPI {

template<DigitalIO::Pin pin_mosi_nr,
         DigitalIO::Pin pin_miso_nr,
         DigitalIO::Pin pin_sck_nr,
         SPI::Polarity polarity,
         SPI::Phase phase,
         SPI::DataOrder data_order>
class Software {
 public:
    static void init() {
        pin_miso.init(DigitalIO::INPUT_PULLUP);
        pin_mosi.init(DigitalIO::OUTPUT);
        pin_sck.init(DigitalIO::OUTPUT);

        if (polarity == SPI::Polarity::idle_high) {
            pin_sck.set();
        } else {
            pin_sck.reset();
        }
    }

    static void disable() {
        pin_miso.init(DigitalIO::INPUT);
        pin_mosi.init(DigitalIO::INPUT);
        pin_sck.init(DigitalIO::INPUT);
    }

    static uint8_t shift(const uint8_t data) {
        if (phase == SPI::Phase::leading_sample) {
            return shift_leading_sample(data);
        } else {
            return shift_trailing_sample(data);
        }
    }

    static uint8_t shift_trailing_sample(const uint8_t data) {
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

    static uint8_t shift_leading_sample(const uint8_t data) {
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
    static constexpr DigitalIO pin_mosi{pin_mosi_nr},
                               pin_miso{pin_miso_nr},
                               pin_sck{pin_sck_nr};

    static bool sample_phase() {
        return pin_miso.read();
    }

    static void output_phase(bool value) {
        pin_mosi.write(value);
    }

    static void delay() {
        _delay_us(10);
    }
};

}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPISOFT__H_
