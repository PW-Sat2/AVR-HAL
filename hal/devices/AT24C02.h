#ifndef HAL_DEVICES_AT24C02_H_
#define HAL_DEVICES_AT24C02_H_

#include "hal/periph.h"

namespace hal {

class AT24C02 {
 public:
    template<std::size_t size>
    class Data {
     public:
        Data(uint8_t addr) : data{_data.data() + 1, size} {
            this->_data[0] = addr;
        }

        libs::span<uint8_t> data;

     private:
        libs::array<uint8_t, size + 1> _data;

        friend class AT24C02;
    };

    AT24C02(I2C::Interface& i2c) : i2c{i2c} {
    }

    template<std::size_t size>
    void write(const Data<size>& mem) const {
        i2c.write(I2CAddress, mem._data);
    }

    template<std::size_t size>
    void read(Data<size>& mem) const {
        libs::array<uint8_t, 1> tx = {mem._data[0]};

        i2c.writeRead(I2CAddress, tx, mem.data);
    }

 private:
    static constexpr I2C::Interface::Address I2CAddress = 0x50;
    I2C::Interface& i2c;
};

}  // namespace hal

#endif  // HAL_DEVICES_AT24C02_H_
