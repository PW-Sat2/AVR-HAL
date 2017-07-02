#ifndef HAL_PERIPH_SPI_HARDWARE_H_
#define HAL_PERIPH_SPI_HARDWARE_H_

#include <avr/io.h>
#include "Interface.h"

#include "hal/libs.h"
#include "hal/mcu.h"
#include "hal/periph/DigitalIO/GPIO.h"

#include "_details.h"

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

template<typename pin_cs,
         HardwareClockDivisor clock_divisor,  //
         SPI::Polarity polarity,              //
         SPI::Phase phase,                    //
         SPI::DataOrder data_order>
class Hardware
    : public details::BlockTransfer<pin_cs,
                                    Hardware<pin_cs, clock_divisor, polarity, phase, data_order>> {
    using Base =
        details::BlockTransfer<pin_cs, Hardware<pin_cs, clock_divisor, polarity, phase, data_order>>;

 public:
    using Base::read;
    using Base::transfer;
    using Base::write;

    static void init() {
        Base::init();
        hal::DigitalIO::GPIO<mcu::pin_mosi>::init(DigitalIO::Mode::OUTPUT);
        hal::DigitalIO::GPIO<mcu::pin_sck>::init(DigitalIO::Mode::OUTPUT);
        hal::DigitalIO::GPIO<mcu::pin_ss>::init(DigitalIO::Mode::OUTPUT);

        SPCR = (1 << SPE) |                                //
               (1 << MSTR) |                               //
               (static_cast<uint8_t>(clock_divisor)) |     //
               (static_cast<uint8_t>(phase) << CPHA) |     //
               (static_cast<uint8_t>(polarity) << CPOL) |  //
               (static_cast<uint8_t>(data_order) << DORD);
    }

    static uint8_t transfer(const uint8_t data) {
        write_data_nowait(data);
        wait_for_transmission_complete();
        return get_data_nowait();
    }

    static void disable() {
        SPCR = 0;
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

}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPI_HARDWARE_H_
