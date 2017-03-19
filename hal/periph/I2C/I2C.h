#ifndef HAL_PERIPH_I2C_I2C_H_
#define HAL_PERIPH_I2C_I2C_H_

#include "array.h"
#include "span.h"
#include <type_traits>
#include <utility>

namespace hal {

class I2C {
 public:
    enum class StartAction : int {
        write = 0,
        read = 1
    };

    enum Acknowledge {
        NACK = 0,
        ACK = 1
    };

    static bool start(uint8_t address, const StartAction start_action);
    static void stop();
    static bool write(const uint8_t data);
    static uint8_t read(Acknowledge ACK);
};

template<typename I2C>
class I2C_Device {
 public:
    constexpr I2C_Device(uint8_t address) : address{address} {
    }

    void write(uint8_t data) const {
        I2C::start(address, I2C::StartAction::write);
        I2C::write(data);
        I2C::stop();
    }

    void write(libs::span<const uint8_t> data) const {
        I2C::start(address, I2C::StartAction::write);
        raw_write(data);
        I2C::stop();
    }

    uint8_t read(typename I2C::Acknowledge last_byte_ACK = I2C::NACK) const {
        I2C::start(address, I2C::StartAction::read);
        uint8_t val = I2C::read(last_byte_ACK);
        I2C::stop();
        return val;
    }

    void read(libs::span<uint8_t> data, typename I2C::Acknowledge last_byte_ACK = I2C::NACK) const {
        I2C::start(address, I2C::StartAction::read);
        raw_read(data, last_byte_ACK);
        I2C::stop();
    }

    void transfer(libs::span<const uint8_t> transmit, libs::span<uint8_t> receive) const {
        I2C::start(address, I2C::StartAction::write);
        raw_write(transmit);
        I2C::start(address, I2C::StartAction::read);
        raw_read(receive);
        I2C::stop();
    }

    void write_register(uint8_t register_address, libs::span<const uint8_t> data) const {
        I2C::start(address, I2C::StartAction::write);
        I2C::write(register_address);
        raw_write(data);
        I2C::stop();
    }

    void read_register(uint8_t register_address, libs::span<uint8_t> data) const {
        I2C::start(address, I2C::StartAction::write);
        I2C::write(register_address);
        I2C::start(address, I2C::StartAction::read);
        raw_read(data);
        I2C::stop();
    }

    void raw_write(libs::span<const uint8_t> data) const {
        auto size = data.size();
        auto ptr = data.data();
        while (size--) {
            I2C::write(*ptr);
            ptr++;
        }
    }

    void raw_read(libs::span<uint8_t> data, typename I2C::Acknowledge last_byte_ACK =
            I2C::NACK) const {
        auto size = data.size() - 1;
        auto ptr = data.data();
        while (size--) {
            *ptr = I2C::read(I2C::ACK);
            ptr++;
        }
        *ptr = I2C::read(last_byte_ACK);
    }

 private:
    uint8_t address;
};

}  // namespace hal

#endif  // HAL_PERIPH_I2C_I2C_H_
