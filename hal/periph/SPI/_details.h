#ifndef HAL_PERIPH_SPI__DETAILS_H_
#define HAL_PERIPH_SPI__DETAILS_H_

#include <avr/io.h>
#include "hal/mcu.h"
#include "Interface.h"

namespace hal {
namespace SPI {

constexpr static DigitalIO::Interface::Pin NoChipSelect = 0xFF;

namespace details {

class BlockTransfer : public Interface {
 public:
    BlockTransfer(DigitalIO::Interface& pin_cs) : pin_cs{pin_cs} {
        pin_cs.init(DigitalIO::Interface::Mode::OUTPUT);
    }

    void transfer(libs::span<const uint8_t> output, libs::span<uint8_t> input) override {
        pin_cs.reset();
        const uint8_t * out_ptr = output.data();
        uint8_t * in_ptr = input.data();
        int len = input.size();
        while (len--) {
            (*in_ptr) = static_cast<Interface*>(this)->transfer(*out_ptr);
            in_ptr++;
            out_ptr++;
        }
        pin_cs.set();
    }

    void write(libs::span<const uint8_t> output) override {
        pin_cs.reset();
        for (auto&& x : output) {
            static_cast<Interface*>(this)->transfer(x);
        }
        pin_cs.set();
    }

    void read(libs::span<uint8_t> input, uint8_t output_value = 0) override {
        pin_cs.reset();
        for (auto& x : input) {
            x = static_cast<Interface*>(this)->transfer(output_value);
        }
        pin_cs.set();
    }

 private:
    DigitalIO::Interface& pin_cs;
};

}  // namespace details
}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPI__DETAILS_H_
