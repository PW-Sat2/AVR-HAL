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
	
	static bool start(uint8_t address, const StartAction_t start_action);
    static void stop();
    static bool write(const uint8_t data);
	static void write(const libs::array_view<const uint8_t> & arv);
    static uint8_t read(Acknowledge_t ACK);    
    static void read(libs::array_view<uint8_t> arv, Acknowledge_t last_byte_ACK = NACK);
};

template<typename I2C, int address>
class I2C_Device_t {
 public:
    static void write(uint8_t data) {
        I2C::start(address, I2C::START_WRITE);
        I2C::write(data);
        I2C::stop();
    }

    static void write(const libs::array_view<uint8_t> arv) {
        I2C::start(address, I2C::START_WRITE);
        I2C::write(arv);
        I2C::stop();
    }

    static void read(I2C_Base::Acknowledge_t ACK) {
        I2C::start(address, I2C::START_READ);
        I2C::read(ACK);
        I2C::stop();
    }

    static void read(libs::array_view<uint8_t> arv, I2C_Base::Acknowledge_t last_byte_ACK = I2C_Base::Acknowledge_t::NACK) {
        I2C::start(address, I2C::START_READ);
        I2C::read(arv, last_byte_ACK);
        I2C::stop();
    }

    static void data_transfer(const libs::array_view<uint8_t> transmit, libs::array_view<uint8_t> receive) {
        I2C::start(address, I2C::START_WRITE);
        I2C::write(transmit);
        I2C::start(address, I2C::START_READ);
        I2C::read(receive);
        I2C::stop();
    }

    static void write_register(uint8_t register_address, const libs::array_view<const uint8_t> data) {
        I2C::start(address, I2C::START_WRITE);
        I2C::write(register_address);
        I2C::write(data);
        I2C::stop();
    }

    static void read_register(uint8_t register_address, libs::array_view<uint8_t> data) {
        I2C::start(address, I2C::START_WRITE);
        I2C::write(register_address);
        I2C::start(address, I2C::START_READ);
        I2C::read(data);
        I2C::stop();
    }
};

}  // namespace hal

#endif  // HAL_PERIPH_I2C_H_
