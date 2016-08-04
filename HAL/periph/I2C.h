#ifndef HAL_PERIPH_I2C_H_
#define HAL_PERIPH_I2C_H_

#include "array.h"
#include "array_view.h"
#include "type_traits.h"

namespace hal {

class I2C {
 public:
    enum class StartAction
        : int {
            write = 0, read = 1
    };

    enum Acknowledge {
        NACK = 0, ACK = 1
    };

    static bool start(uint8_t address, const StartAction start_action);
    static void stop();
    static bool write(const uint8_t data);
    static uint8_t read(Acknowledge ACK);
};

template<typename I2C, int address>
class I2C_Device {
 public:
    static void write(uint8_t data) {
        I2C::start(address, I2C::StartAction::write);
        I2C::write(data);
        I2C::stop();
    }

    template<typename T, typename enable_if<
            !is_integral<remove_reference<T>>::value>::type>
    static void write(T&& arv) {
        I2C::start(address, I2C::StartAction::write);
        raw_write(arv);
        I2C::stop();
    }

    static uint8_t read() {
        I2C::start(address, I2C::StartAction::read);
        uint8_t val = I2C::read(I2C::NACK);
        I2C::stop();
        return val;
    }

    template<typename T>
    static void read(T&& arv) {
        I2C::start(address, I2C::StartAction::read);
        raw_read(arv);
        I2C::stop();
    }

    template<typename T, typename T2>
    static void data_transfer(T&& transmit, T2&& receive) {
        I2C::start(address, I2C::StartAction::write);
        raw_write(transmit);
        I2C::start(address, I2C::StartAction::read);
        raw_read(receive);
        I2C::stop();
    }

    template<typename T>
    static void write_register(uint8_t register_address, T&& data) {
        I2C::start(address, I2C::StartAction::write);
        I2C::write(register_address);
        raw_write(data);
        I2C::stop();
    }

    template<typename T>
    static void read_register(uint8_t register_address, T&& data) {
        I2C::start(address, I2C::StartAction::write);
        I2C::write(register_address);
        I2C::start(address, I2C::StartAction::read);
        raw_read(data);
        I2C::stop();
    }

    template<typename T>
    static void raw_write(T&& arv) {
        auto size = arv.size();
        auto data = arv.data();
        while (size--) {
            I2C::write(*data);
            data++;
        }
    }

    template<typename T>
    static void raw_read(T&& arv, typename I2C::Acknowledge last_byte_ACK =
            I2C::NACK) {
        auto size = arv.size() - 1;
        auto data = arv.data();
        while (size--) {
            *data = I2C::read(I2C::ACK);
            data++;
        }
        *data = I2C::read(last_byte_ACK);
    }
};

}  // namespace hal

#endif  // HAL_PERIPH_I2C_H_
