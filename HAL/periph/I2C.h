#ifndef HAL_PERIPH_I2C_H_
#define HAL_PERIPH_I2C_H_

#include "array_view.h"

namespace hal {

class I2C_Base {
 public:
    enum StartAction_t {
        START_WRITE = 0,
        START_READ = 1
    };

    enum Acknowledge_t {
        NACK = 0,
        ACK = 1
    };
};

template<typename I2C>
class I2C_Device_t {
 public:
    constexpr I2C_Device_t(uint8_t address) : address(address) {
    }

    void write(uint8_t data) const {
        I2C::start(this->address, I2C::START_WRITE);
        I2C::write(data);
        I2C::stop();
    }

    void write(const libs::array_view<uint8_t> arv) const {
        I2C::start(this->address, I2C::START_WRITE);
        I2C::write(arv);
        I2C::stop();
    }

    void read(I2C_Base::Acknowledge_t ACK) const {
        I2C::start(this->address, I2C::START_READ);
        I2C::read(ACK);
        I2C::stop();
    }

    void read(libs::array_view<uint8_t> arv, I2C_Base::Acknowledge_t last_byte_ACK = I2C_Base::Acknowledge_t::NACK) const {
        I2C::start(this->address, I2C::START_READ);
        I2C::read(arv, last_byte_ACK);
        I2C::stop();
    }

    void data_transfer(const libs::array_view<uint8_t> transmit, libs::array_view<uint8_t> receive) const {
        I2C::start(this->address, I2C::START_WRITE);
        I2C::write(transmit);
        I2C::start(this->address, I2C::START_READ);
        I2C::read(receive);
        I2C::stop();
    }

    void write_register(uint8_t register_address, const libs::array_view<const uint8_t> data) const {
        I2C::start(this->address, I2C::START_WRITE);
        I2C::write(register_address);
        I2C::write(data);
        I2C::stop();
    }

    void read_register(uint8_t register_address, libs::array_view<uint8_t> data) const {
        I2C::start(this->address, I2C::START_WRITE);
        I2C::write(register_address);
        I2C::start(this->address, I2C::START_READ);
        I2C::read(data);
        I2C::stop();
    }

 private:
    const uint8_t address;
};

}  // namespace hal

#endif  // HAL_PERIPH_I2C_H_
