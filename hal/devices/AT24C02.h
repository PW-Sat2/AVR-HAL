#ifndef HAL_DEVICES_AT24C02_H_
#define HAL_DEVICES_AT24C02_H_

#include "hal/periph.h"

namespace hal {
namespace devices {
namespace AT24C02 {

template<typename i2c>
class AT24C02;

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

static constexpr I2C::Address I2CAddress = 0x50;

template<typename i2c>
struct AT24C02 : libs::PureStatic {
    template<std::size_t size>
    static void write(const Data<size>& mem) {
        i2c::write(I2CAddress, mem._data);
    }

    template<std::size_t size>
    static void read(Data<size>& mem) {
        i2c::write_read(I2CAddress, {mem._data[0]}, mem.data);
    }
};

}  // namespace AT24C02
}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_AT24C02_H_
