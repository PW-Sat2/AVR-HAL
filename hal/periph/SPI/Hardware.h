#ifndef HAL_PERIPH_SPI_HARDWARE_H_
#define HAL_PERIPH_SPI_HARDWARE_H_

#include <avr/io.h>
#include "Interface.h"

#include "hal/mcu.h"
#include "hal/libs.h"
#include "hal/periph/GPIO/IDigitalIO.h"
#include "hal/periph/GPIO/DigitalIO.h"

#include "_chip_select.h"

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

enum class Polarity : int {
    idle_low = 0,
    idle_high = 1
};

enum class Phase : int {
    leading_sample = 0,
    trailing_sample = 1
};

enum class DataOrder : int {
    MSB_first = 0,
    LSB_first = 1
};

enum class HardwareClockDivisor {
    SPIHard_DIV_4 = 0,
    SPIHard_DIV_16 = 1,
    SPIHard_DIV_64 = 2,
    SPIHard_DIV_128 = 3
};

template<IDigitalIO::Pin pin_chip_select,
         HardwareClockDivisor clock_divisor,
         SPI::Polarity polarity,
         SPI::Phase phase,
         SPI::DataOrder data_order>
class Hardware : public details::BlockTransfer<pin_chip_select> {
 public:
    void init() {
        pin_mosi.init(IDigitalIO::Mode::OUTPUT);
        pin_sck.init(IDigitalIO::Mode::OUTPUT);
        pin_ss.init(IDigitalIO::Mode::OUTPUT);

        SPCR = (1 << SPE)  |
               (1 << MSTR) |
               (static_cast<uint8_t>(clock_divisor)) |
               (static_cast<uint8_t>(phase) << CPHA) |
               (static_cast<uint8_t>(polarity) << CPOL) |
               (static_cast<uint8_t>(data_order) << DORD);
    }

    uint8_t transfer(const uint8_t data) override {
        write_data_nowait(data);
        wait_for_transmission_complete();
        return get_data_nowait();
    }

    void disable() {
        SPCR = 0;
    }

    void wait_for_transmission_complete() {
        while (!is_transmission_complete()) {
        }
    }

    bool is_transmission_complete() {
        return (libs::read_bit(SPSR, SPIF) == true);
    }

    // functions for interrupt-driven usage

    void write_data_nowait(uint8_t data) {
        SPDR = data;
    }

    uint8_t get_data_nowait() {
        return SPDR;
    }

    void enable_interrupt() {
        libs::set_bit(SPCR, SPIE);
    }

 private:
    DigitalIO<mcu::pin_mosi> pin_mosi;
    DigitalIO<mcu::pin_sck> pin_sck;
    DigitalIO<mcu::pin_ss> pin_ss;
};

}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPI_HARDWARE_H_
