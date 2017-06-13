#ifndef HAL_PERIPH_SPI_SOFTWARE_H_
#define HAL_PERIPH_SPI_SOFTWARE_H_

#include <avr/io.h>
#include <util/delay.h>

#include "hal/libs.h"
#include "hal/mcu.h"
#include "hal/periph/DigitalIO/Interface.h"

#include "Interface.h"

namespace hal {
namespace SPI {

template<typename pin_mosi,
    typename pin_miso,
    typename pin_sck,
    typename pin_ss,
    SPI::Polarity polarity, SPI::Phase phase>
class Software : public details::BlockTransfer<pin_ss, Software<pin_mosi, pin_miso, pin_sck, pin_ss, polarity, phase>> {
 public:
    using details::BlockTransfer<pin_ss, Software<pin_mosi, pin_miso, pin_sck, pin_ss, polarity, phase>>::write;
    using details::BlockTransfer<pin_ss, Software<pin_mosi, pin_miso, pin_sck, pin_ss, polarity, phase>>::read;
    using details::BlockTransfer<pin_ss, Software<pin_mosi, pin_miso, pin_sck, pin_ss, polarity, phase>>::transfer;

    Software() = delete;
    Software(Software&) = delete;
    Software(Software&&) = delete;

    static void init() {
        pin_miso::init(DigitalIO::Mode::INPUT_PULLUP);
        pin_mosi::init(DigitalIO::Mode::OUTPUT);
        pin_sck::init(DigitalIO::Mode::OUTPUT);

        if (polarity == SPI::Polarity::idle_high) {
            pin_sck::set();
        } else {
            pin_sck::reset();
        }
    }

    static void disable() {
        pin_miso::init(DigitalIO::Mode::INPUT);
        pin_mosi::init(DigitalIO::Mode::INPUT);
        pin_sck::init(DigitalIO::Mode::INPUT);
    }

    static uint8_t transfer(const uint8_t data) {
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
            pin_sck::toggle();
            delay();
            output |= (sample_phase() << i);
            pin_sck::toggle();
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
            pin_sck::toggle();
            delay();
            pin_sck::toggle();
        }
        return output;
    }

 private:
    static bool sample_phase() {
        return pin_miso::read();
    }

    static void output_phase(bool value) {
        pin_mosi::write(value);
    }

    static void delay() {
        _delay_us(10);
    }
};

}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPI_SOFTWARE_H_
