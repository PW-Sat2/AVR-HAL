#ifndef HAL_DEVICES_AT24C02_H_
#define HAL_DEVICES_AT24C02_H_

#include "hal/periph.h"

namespace hal {

template<typename i2c>
class AT24C02;

struct AT24C02_ {
    template<std::size_t size>
    class Data {
     public:
        Data(uint8_t addr) : data{_data.data() + 1, size} {
            this->_data[0] = addr;
        }

        gsl::span<uint8_t> data;

     protected:
        std::array<uint8_t, size + 1> _data;

        template<typename i2c>
        friend class AT24C02;
    };
};

template<typename i2c>
class AT24C02 : public AT24C02_ {
 public:
    template<std::size_t size>
    static void write(const Data<size>& mem) {
        i2c::write(I2CAddress, mem._data);
    }

    template<std::size_t size>
    static void read(Data<size>& mem) {
        std::array<uint8_t, 1> tx = {mem._data[0]};

        i2c::write_read(I2CAddress, tx, mem.data);
    }

 private:
    static constexpr I2C::Interface::Address I2CAddress = 0x50;
};

}  // namespace hal

#endif  // HAL_DEVICES_AT24C02_H_
