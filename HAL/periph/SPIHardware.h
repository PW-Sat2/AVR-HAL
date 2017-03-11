#ifndef HAL_PERIPH_SPIHARDWARE_H_
#define HAL_PERIPH_SPIHARDWARE_H_

#include <avr/io.h>
#include "SPI.h"

#include "mcu.h"
#include "bit_operations.h"
#include "DigitalIO.h"
#include "array.h"

// workaround for newer MCUs...
#ifndef SPCR
#define SPCR SPCR0
#define SPSR SPSR0
#define SPIF SPIF0
#define SPDR SPDR0

#define SPE SPE0
#define SPIE SPIE0
#define MSTR MSTR0
#define CPHA CPHA0
#define CPOL CPOL0
#define DORD DORD0
#endif

namespace hal {
namespace SPI {


enum class HardwareClockDivisor {
    SPIHard_DIV_4 = 0,
    SPIHard_DIV_16 = 1,
    SPIHard_DIV_64 = 2,
    SPIHard_DIV_128 = 3
};

template<HardwareClockDivisor clock_divisor,
         SPI::Polarity polarity,
         SPI::Phase phase,
         SPI::DataOrder data_order>
class Hardware {
 public:
    static void init() {
        pin_mosi.init(DigitalIO::OUTPUT);
        pin_sck.init(DigitalIO::OUTPUT);
        pin_ss.init(DigitalIO::OUTPUT);

        SPCR = (1 << SPE)  |
               (1 << MSTR) |
               (static_cast<uint8_t>(clock_divisor)) |
               (static_cast<uint8_t>(phase) << CPHA) |
               (static_cast<uint8_t>(polarity) << CPOL) |
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

 private:
    static constexpr DigitalIO pin_mosi{mcu::pin_mosi},
                               pin_sck{mcu::pin_sck},
                               pin_ss{mcu::pin_ss};
};

}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPIHARDWARE_H_
