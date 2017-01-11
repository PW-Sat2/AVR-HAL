#ifndef HAL_PERIPH_SPI_H_
#define HAL_PERIPH_SPI_H_

#include <avr/io.h>
#include "mcu.h"
#include "bit_operations.h"
#include "DigitalIO.h"
#include "array.h"

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

template<typename spi>
class Device {
 public:
    constexpr explicit Device(const DigitalIO::Pin pin_cs) :
            pin_cs{pin_cs} {
    }

    constexpr explicit Device(const DigitalIO::Pin pin_cs, DigitalIO::RUNTIME) :
            pin_cs{pin_cs, DigitalIO::RUNTIME::ENABLED} {
    }

    void init() const {
        this->pin_cs.init(DigitalIO::OUTPUT);
        this->disable();
    }

    void enable() const {
        this->pin_cs.reset();
    }

    void disable() const {
        this->pin_cs.set();
    }

    uint8_t shift(const uint8_t data) const {
        return spi::shift(data);
    }

    uint8_t transfer(const uint8_t data) const {
        this->enable();
        uint8_t x = spi::shift(data);
        this->disable();
        return x;
    }

    template<typename T, typename T2>
    void transfer(T&& output, T2&& input) const {
        this->enable();
        const uint8_t * out_ptr = output.data();
        uint8_t * in_ptr = input.data();
        int len = input.size();
        while (len--) {
            (*in_ptr) = spi::shift(*out_ptr);
            in_ptr++;
            out_ptr++;
        }
        this->disable();
    }

    template<typename T>
    void transmit(T&& data) const {
        this->enable();
        for (auto&& x : data) {
            spi::shift(x);
        }
        this->disable();
    }

    template<typename T>
    void receive(T&& data, uint8_t output_value = 0) const {
        this->enable();
        for (auto& x : data) {
            x = spi::shift(output_value);
        }
        this->disable();
    }

 private:
     const DigitalIO pin_cs;
};

}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPI_H_
