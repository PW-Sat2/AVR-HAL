#ifndef HAL_DEVICES_AD5641_H_
#define HAL_DEVICES_AD5641_H_

#include "hal/periph.h"

namespace hal {

class AD5641 {
 public:
    constexpr AD5641(hal::SPI::Interface& device) : spi_dev(device) {
    }

    void write(uint16_t data_lsb) {
        if (data_lsb >= libs::power_of_two<14>()) {
            data_lsb = libs::power_of_two<14>() - 1;
        }

        libs::array<uint8_t, 2> data;
        libs::Writer writer{data};
        writer.WriteLowerBytesBE(data_lsb, 2);

        spi_dev.write(data);
    }

 private:
    hal::SPI::Interface& spi_dev;
};

}  // namespace hal


#endif  // HAL_DEVICES_AD5641_H_
