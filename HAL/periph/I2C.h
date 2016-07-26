#ifndef HAL_PERIPH_I2C_H_
#define HAL_PERIPH_I2C_H_

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

    void write(uint8_t * data, uint8_t len) const {
        I2C::start(this->address, I2C::START_WRITE);
        I2C::write(data, len);
        I2C::stop();
    }

    void read(I2C_Base::Acknowledge_t ACK) const {
        I2C::start(this->address, I2C::START_READ);
        I2C::read(ACK);
        I2C::stop();
    }

    void read(uint8_t * data_out, uint8_t len, I2C_Base::Acknowledge_t last_byte_ACK) const {
        I2C::start(this->address, I2C::START_READ);
        I2C::read(data_out, len, last_byte_ACK);
        I2C::stop();
    }

    void data_transfer(uint8_t * out_data, uint8_t out_len, uint8_t * in_data, uint8_t in_len) const {
        I2C::start(this->address, I2C::START_WRITE);
        I2C::write(out_data, out_len);
        I2C::start(this->address, I2C::START_READ);
        I2C::read(in_data, in_len, I2C::NACK);
        I2C::stop();
    }

    void write_register(uint8_t register_address, uint8_t * data, uint8_t len) const {
        I2C::start(this->address, I2C::START_WRITE);
        I2C::write(register_address);
        I2C::write(data, len);
        I2C::stop();
    }

    void read_register(uint8_t register_address, uint8_t * data, uint8_t len) const {
        this->data_transfer(&register_address, 1, data, len);
    }

 private:
    const uint8_t address;
};

}  // namespace hal

#endif  // HAL_PERIPH_I2C_H_
