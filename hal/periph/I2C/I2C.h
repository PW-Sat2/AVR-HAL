#ifndef HAL_PERIPH_I2C_I2C_H_
#define HAL_PERIPH_I2C_I2C_H_

#include <type_traits>
#include <utility>

#include "hal/libs.h"

namespace hal {

class II2C {
 public:
    enum class StartAction : int {
        write = 0,
        read = 1
    };

    enum Acknowledge {
        NACK = 0,
        ACK = 1
    };

    virtual bool start(uint8_t address, const StartAction start_action) = 0;
    virtual void stop() = 0;
    virtual bool write(const uint8_t data) = 0;
    virtual uint8_t read(Acknowledge ACK) = 0;
};

class I2C_Device {
 public:
    constexpr I2C_Device(II2C& i2c, uint8_t address) : i2c{i2c}, address{address} {
    }

    void write(uint8_t data) const {
        i2c.start(address, II2C::StartAction::write);
        i2c.write(data);
        i2c.stop();
    }

    void write(libs::span<const uint8_t> data) const {
        i2c.start(address, II2C::StartAction::write);
        raw_write(data);
        i2c.stop();
    }

    uint8_t read(II2C::Acknowledge last_byte_ACK = II2C::NACK) const {
        i2c.start(address, II2C::StartAction::read);
        uint8_t val = i2c.read(last_byte_ACK);
        i2c.stop();
        return val;
    }

    void read(libs::span<uint8_t> data, II2C::Acknowledge last_byte_ACK = II2C::NACK) const {
        i2c.start(address, II2C::StartAction::read);
        raw_read(data, last_byte_ACK);
        i2c.stop();
    }

    void transfer(libs::span<const uint8_t> transmit, libs::span<uint8_t> receive) const {
        i2c.start(address, II2C::StartAction::write);
        raw_write(transmit);
        i2c.start(address, II2C::StartAction::read);
        raw_read(receive);
        i2c.stop();
    }

    void write_register(uint8_t register_address, libs::span<const uint8_t> data) const {
        i2c.start(address, II2C::StartAction::write);
        i2c.write(register_address);
        raw_write(data);
        i2c.stop();
    }

    void read_register(uint8_t register_address, libs::span<uint8_t> data) const {
        i2c.start(address, II2C::StartAction::write);
        i2c.write(register_address);
        i2c.start(address, II2C::StartAction::read);
        raw_read(data);
        i2c.stop();
    }

    void raw_write(libs::span<const uint8_t> data) const {
        auto size = data.size();
        auto ptr = data.data();
        while (size--) {
            i2c.write(*ptr);
            ptr++;
        }
    }

    void raw_read(libs::span<uint8_t> data, II2C::Acknowledge last_byte_ACK =
            II2C::NACK) const {
        auto size = data.size() - 1;
        auto ptr = data.data();
        while (size--) {
            *ptr = i2c.read(II2C::ACK);
            ptr++;
        }
        *ptr = i2c.read(last_byte_ACK);
    }

 private:
    II2C& i2c;
    uint8_t address;
};

}  // namespace hal

#endif  // HAL_PERIPH_I2C_I2C_H_
