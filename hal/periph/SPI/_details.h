#ifndef HAL_PERIPH_SPI__DETAILS_H_
#define HAL_PERIPH_SPI__DETAILS_H_

#include <avr/io.h>
#include "Interface.h"
#include "hal/mcu.h"

namespace hal {
namespace SPI {

constexpr static DigitalIO::Pin NoChipSelect = 0xFF;

namespace details {

template<typename GPIO>
class BlockTransfer : public Interface {
 public:
    BlockTransfer() {
        GPIO::init(DigitalIO::Mode::OUTPUT);
    }

    void
    transfer(gsl::span<const uint8_t> output, gsl::span<uint8_t> input) override {
        GPIO::reset();
        const uint8_t* out_ptr = output.data();
        uint8_t* in_ptr        = input.data();
        int len                = input.size();
        while (len--) {
            (*in_ptr) = static_cast<Interface*>(this)->transfer(*out_ptr);
            in_ptr++;
            out_ptr++;
        }
        GPIO::set();
    }

    void write(gsl::span<const uint8_t> output) override {
        GPIO::reset();
        for (auto&& x : output) {
            static_cast<Interface*>(this)->transfer(x);
        }
        GPIO::set();
    }

    void read(gsl::span<uint8_t> input, uint8_t output_value = 0) override {
        GPIO::reset();
        for (auto& x : input) {
            x = static_cast<Interface*>(this)->transfer(output_value);
        }
        GPIO::set();
    }
};

}  // namespace details
}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPI__DETAILS_H_
