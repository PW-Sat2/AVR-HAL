#ifndef HAL_PERIPH_I2C__DETAILS_H_
#define HAL_PERIPH_I2C__DETAILS_H_

#include <type_traits>
#include <utility>

#include "hal/libs.h"

namespace hal {
namespace I2C {
namespace details {

class _Interface : public Interface {
 public:
    void write(uint8_t address, gsl::span<const uint8_t> data) override {
        start(address, StartAction::write);
        for (auto i : data) {
            write(i);
        }
        stop();
    }

    void read(uint8_t address, gsl::span<uint8_t> data) override {
        start(address, StartAction::read);
        raw_read(data);
        stop();
    }

    void write_read(uint8_t address,
                    gsl::span<const uint8_t> output,
                    gsl::span<uint8_t> input) override {
        start(address, StartAction::write);
        raw_write(output);
        start(address, StartAction::read);
        raw_read(input);
        stop();
    }

 protected:
    enum class StartAction : int {
        write = 0,
        read  = 1,
    };

    enum Acknowledge {
        NACK = 0,
        ACK  = 1,
    };

    void raw_write(gsl::span<const uint8_t> data) {
        for (auto i : data) {
            write(i);
        }
    }

    void raw_read(gsl::span<uint8_t> data) {
        for (size_t i = 0; i < data.size(); ++i) {
            data[i] = read((i == data.size() - 1) ? NACK : ACK);
        }
    }

    virtual bool start(uint8_t address, const StartAction start_action) = 0;
    virtual void stop()                                                 = 0;
    virtual bool write(const uint8_t data)                              = 0;
    virtual uint8_t read(Acknowledge ACK)                               = 0;
};

}  // namespace details
}  // namespace I2C
}  // namespace hal

#endif  // HAL_PERIPH_I2C__DETAILS_H_
