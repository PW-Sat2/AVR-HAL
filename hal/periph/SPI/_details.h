#ifndef HAL_PERIPH_SPI__DETAILS_H_
#define HAL_PERIPH_SPI__DETAILS_H_

#include <avr/io.h>
#include "Interface.h"
#include "hal/mcu.h"

namespace hal {
namespace SPI {
namespace details {

template<typename pin_cs, typename T>
class BlockTransfer : libs::PureStatic {
 public:
    static void init() {
        pin_cs::set();
        pin_cs::init(DigitalIO::Mode::OUTPUT);
    }

    static void
    transfer(gsl::span<const uint8_t> output, gsl::span<uint8_t> input) {
        pin_cs::reset();
        const uint8_t* out_ptr = output.data();
        uint8_t* in_ptr        = input.data();
        int len                = input.size();
        while (len--) {
            (*in_ptr) = T::transfer(*out_ptr);
            in_ptr++;
            out_ptr++;
        }
        pin_cs::set();
    }

    static void write(gsl::span<const uint8_t> output) {
        pin_cs::reset();
        for (auto&& x : output) {
            T::transfer(x);
        }
        pin_cs::set();
    }

    static void read(gsl::span<uint8_t> input, uint8_t output_value = 0) {
        pin_cs::reset();
        for (auto& x : input) {
            T::transfer(output_value);
        }
        pin_cs::set();
    }
};

}  // namespace details
}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPI__DETAILS_H_
