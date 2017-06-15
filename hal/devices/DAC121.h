#ifndef HAL_DEVICES_DAC121_H_
#define HAL_DEVICES_DAC121_H_

#include "hal/libs.h"
#include "hal/periph.h"

namespace hal {
namespace drivers {

class DAC121 {
 public:
    explicit DAC121(SPI::Interface& spi_dev) : spi_dev{spi_dev} {
    }

    enum class PowerDownMode : std::uint8_t {
        ToGnd1k   = 1 << 4,
        ToGnd100k = 2 << 4,
        HiZ       = 3 << 4
    };

    void set_power_down_mode(PowerDownMode new_power_down_mode) {
        const std::array<std::uint8_t, 2> data_out = {
            static_cast<std::uint8_t>(static_cast<std::uint8_t>(new_power_down_mode)),
            0};

        spi_dev.write(data_out);
    }

    void write_to_output(std::uint16_t raw_value) {
        std::array<std::uint8_t, 2> data_out;
        libs::Writer writer{data_out};

        writer.WriteByte(static_cast<std::uint8_t>(OperationMode::NormalOperation) |
                         ((raw_value >> 8) & 0x0F));
        writer.WriteByte(raw_value & 0xFF);

        spi_dev.write(data_out);
    }

 private:
    SPI::Interface& spi_dev;

    enum class OperationMode : std::uint8_t { NormalOperation = 0 << 4 };
};

}  // namespace drivers
}  // namespace hal

#endif  // HAL_DEVICES_DAC121_H_
