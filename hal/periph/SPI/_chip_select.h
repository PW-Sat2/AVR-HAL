#ifndef HAL_PERIPH_SPI__CHIP_SELECT_H_
#define HAL_PERIPH_SPI__CHIP_SELECT_H_

#include <avr/io.h>
#include "hal/mcu.h"
#include "Interface.h"

namespace hal {
namespace SPI {

constexpr static IDigitalIO::Pin NoChipSelect = 0xFF;

namespace details {

template<IDigitalIO::Pin pin>
class ChipSelectHandling {
 public:
    static void enable() {
        pin_cs.reset();
    }

    static void disable() {
        pin_cs.set();
    }
 private:
    static DigitalIO<pin> pin_cs;
};

template<>
class ChipSelectHandling<NoChipSelect> {
 public:
    static void enable() {
    }

    static void disable() {
    }
};

template<IDigitalIO::Pin pin>
class BlockTransfer : public Interface {
 public:
    void transfer(libs::span<const uint8_t> output, libs::span<uint8_t> input) override {
        chipSelectHandling.enable();
        const uint8_t * out_ptr = output.data();
        uint8_t * in_ptr = input.data();
        int len = input.size();
        while (len--) {
            (*in_ptr) = static_cast<Interface*>(this)->transfer(*out_ptr);
            in_ptr++;
            out_ptr++;
        }
        chipSelectHandling.disable();
    }

    void write(libs::span<const uint8_t> output) override {
        chipSelectHandling.enable();
        for (auto&& x : output) {
            static_cast<Interface*>(this)->transfer(x);
        }
        chipSelectHandling.disable();
    }

    void read(libs::span<uint8_t> input, uint8_t output_value = 0) override {
        chipSelectHandling.enable();
        for (auto& x : input) {
            x = static_cast<Interface*>(this)->transfer(output_value);
        }
        chipSelectHandling.disable();
    }

 private:
    ChipSelectHandling<pin> chipSelectHandling;
};

}  // namespace details
}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPI__CHIP_SELECT_H_
