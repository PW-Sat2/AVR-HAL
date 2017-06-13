#ifndef HAL_DEVICES_AD5641_H_
#define HAL_DEVICES_AD5641_H_

#include <array>
#include "hal/periph.h"

namespace hal {
namespace devices {

template<typename SPI>
struct AD5641 {
    static void write(uint16_t data_lsb) {
        if (data_lsb >= libs::power_of_two<14>()) {
            data_lsb = libs::power_of_two<14>() - 1;
        }

        std::array<uint8_t, 2> data;
        libs::Writer writer{data};
        writer.WriteLowerBytesBE(data_lsb, 2);

        SPI::write(data);
    }
};

}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_AD5641_H_
