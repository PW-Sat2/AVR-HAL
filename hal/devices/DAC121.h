#ifndef HAL_DEVICES_DAC121_H_
#define HAL_DEVICES_DAC121_H_

#include "hal/libs.h"
#include "hal/periph.h"

namespace hal {
namespace devices {
namespace DAC121 {

enum class PowerDownMode : std::uint8_t {
    ToGnd1k   = 1 << 4,
    ToGnd100k = 2 << 4,
    HiZ       = 3 << 4
};

template<typename SPI>
struct DAC121 : libs::PureStatic {
    static void set_power_down_mode(PowerDownMode new_power_down_mode) {
        const std::array<std::uint8_t, 2> data_out = {num(new_power_down_mode), 0};

        SPI::write(data_out);
    }

    static void write_to_output(uint12_t raw_value) {
        std::array<std::uint8_t, 2> data_out;
        libs::Writer writer{data_out};

        writer.WriteByte((raw_value >> 8) & 0x0F);
        writer.WriteByte(raw_value & 0xFF);

        SPI::write(data_out);
    }
};

};  // namespace DAC121
}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_DAC121_H_
