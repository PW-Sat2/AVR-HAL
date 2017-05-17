#ifndef HAL_PERIPH_SPI_SPI_H_
#define HAL_PERIPH_SPI_SPI_H_

#include <avr/io.h>
#include "hal/mcu.h"
#include "hal/libs/bit_operations.h"
#include "hal/periph/GPIO/DigitalIO.h"
#include "hal/libs/array.h"

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


class ISPI {
 public:
    virtual uint8_t shift(const uint8_t data) = 0;
};


class Device {
 public:
    constexpr Device(ISPI& spi, IDigitalIO& pin_cs) :
            spi{spi}, pin_cs{pin_cs} {
    }

    void init() const {
        this->pin_cs.init(IDigitalIO::Mode::OUTPUT);
        this->disable();
    }

    void enable() const {
        this->pin_cs.reset();
    }

    void disable() const {
        this->pin_cs.set();
    }

    uint8_t shift(const uint8_t data) const {
        return spi.shift(data);
    }

    uint8_t transfer(const uint8_t data) const {
        this->enable();
        uint8_t x = spi.shift(data);
        this->disable();
        return x;
    }

    void transfer(libs::span<const uint8_t> output, libs::span<uint8_t> input) const {
        this->enable();
        const uint8_t * out_ptr = output.data();
        uint8_t * in_ptr = input.data();
        int len = input.size();
        while (len--) {
            (*in_ptr) = spi.shift(*out_ptr);
            in_ptr++;
            out_ptr++;
        }
        this->disable();
    }

    void write(libs::span<const uint8_t> data) const {
        this->enable();
        for (auto&& x : data) {
            spi.shift(x);
        }
        this->disable();
    }

    void read(libs::span<uint8_t> data, uint8_t output_value = 0) const {
        this->enable();
        for (auto& x : data) {
            x = spi.shift(output_value);
        }
        this->disable();
    }

 private:
    ISPI& spi;
    IDigitalIO& pin_cs;
};

}  // namespace SPI
}  // namespace hal

#endif  // HAL_PERIPH_SPI_SPI_H_
