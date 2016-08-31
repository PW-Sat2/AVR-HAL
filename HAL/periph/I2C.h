#ifndef HAL_PERIPH_I2C_H_
#define HAL_PERIPH_I2C_H_

#include "array.h"
#include "array_view.h"
#include <type_traits>
#include <utility>

namespace hal {

class I2C {
 public:
    enum class StartAction
        : int {
            write = 0, read = 1
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

    template<typename T, typename =
             typename std::enable_if<
                          !std::is_integral<
                              typename std::remove_reference<T>::type
                          >::value
                      >::type>
    void write(T&& arv) const {
        I2C::start(address, I2C::StartAction::write);
        raw_write(std::forward<T>(arv));
        I2C::stop();
    }

    uint8_t read(typename I2C::Acknowledge last_byte_ACK = I2C::NACK) const {
        I2C::start(address, I2C::StartAction::read);
        uint8_t val = I2C::read(last_byte_ACK);
        I2C::stop();
        return val;
    }

    template<typename T>
    void read(T&& arv, typename I2C::Acknowledge last_byte_ACK = I2C::NACK) const {
        I2C::start(address, I2C::StartAction::read);
        raw_read(arv, last_byte_ACK);
        I2C::stop();
    }

    template<typename T, typename T2>
    void data_transfer(T&& transmit, T2&& receive) const {
        I2C::start(address, I2C::StartAction::write);
        raw_write(transmit);
        I2C::start(address, I2C::StartAction::read);
        raw_read(receive);
        I2C::stop();
    }

    template<typename T>
    void write_register(uint8_t register_address, T&& data) const {
        I2C::start(address, I2C::StartAction::write);
        I2C::write(register_address);
        raw_write(data);
        I2C::stop();
    }

    template<typename T>
    void read_register(uint8_t register_address, T&& data) const {
        I2C::start(address, I2C::StartAction::write);
        I2C::write(register_address);
        I2C::start(address, I2C::StartAction::read);
        raw_read(data);
        I2C::stop();
    }

    template<typename T>
    void raw_write(T&& arv) const {
        auto size = arv.size();
        auto data = arv.data();
        while (size--) {
            I2C::write(*data);
            data++;
        }
    }

    template<typename T>
    void raw_read(T&& arv, typename I2C::Acknowledge last_byte_ACK =
            I2C::NACK) const {
        auto size = arv.size() - 1;
        auto data = arv.data();
        while (size--) {
            *data = I2C::read(I2C::ACK);
            data++;
        }
        *data = I2C::read(last_byte_ACK);
    }

 private:
    uint8_t address;
};

}  // namespace hal

#endif  // HAL_PERIPH_I2C_H_
