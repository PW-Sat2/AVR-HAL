#ifndef HAL_PERIPH_SPI_SPISLAVE_H_
#define HAL_PERIPH_SPI_SPISLAVE_H_

#include <avr/io.h>
#include "hal/libs.h"
#include "hal/mcu.h"

namespace hal {

class SPISlave : libs::PureStatic {
    using pin_mosi = DigitalIO::GPIO<mcu::pin_mosi>;
    using pin_miso = DigitalIO::GPIO<mcu::pin_miso>;
    using pin_sck  = DigitalIO::GPIO<mcu::pin_sck>;
    using pin_ss   = DigitalIO::GPIO<mcu::pin_ss>;

 public:
    enum class Polarity : int {
        idle_low  = 0,
        idle_high = 1,
    };

    enum class Phase : int {
        leading_sample  = 0,
        trailing_sample = 1,
    };

    enum class DataOrder : int {
        MSB_first = 0,
        LSB_first = 1,
    };

    enum class ClockDivisor : int {
        DIV_4   = 0,
        DIV_16  = 1,
        DIV_64  = 2,
        DIV_128 = 3,
    };

    static void
    init(const Polarity polarity, const Phase phase, const DataOrder data_order) {
        pin_mosi::init(DigitalIO::Mode::INPUT);
        pin_sck::init(DigitalIO::Mode::INPUT);
        pin_ss::init(DigitalIO::Mode::INPUT);
        pin_miso::init(DigitalIO::Mode::OUTPUT);

        SPCR = (1 << SPE) |                                //
               (static_cast<uint8_t>(phase) << CPHA) |     //
               (static_cast<uint8_t>(polarity) << CPOL) |  //
               (static_cast<uint8_t>(data_order) << DORD);
    }

    static void disable() {
        SPCR = 0;
    }

    static uint8_t shift(const uint8_t data) {
        write_data_nowait(data);
        wait_for_transmission_complete();
        return get_data_nowait();
    }

    static void wait_for_transmission_complete() {
        while (!is_transmission_complete()) {
        }
    }

    static bool is_transmission_complete() {
        return (libs::read_bit(SPSR, SPIF) == true);
    }

    // functions for interrupt-driven usage

    static void write_data_nowait(uint8_t data) {
        SPDR = data;
    }

    static uint8_t get_data_nowait() {
        return SPDR;
    }

    static void enable_interrupt() {
        libs::set_bit(SPCR, SPIE);
    }
};

}  // namespace hal

#endif  // HAL_PERIPH_SPI_SPISLAVE_H_
