#ifndef HAL_DEVICES_DAC121_H_
#define HAL_DEVICES_DAC121_H_

#include "hal/periph.h"

namespace hal {
namespace drivers {

class DAC121 {
 public:
    enum Mode {
        NormalOperation = 0 << 4,
        PowerDown_1kToGnd  = 1 << 4,
        PowerDown_100kToGnd  = 2 << 4,
        PowerDown_HiZ = 3 << 4
    };

    explicit DAC121(SPI::Interface& spi_dev) : spi_dev{spi_dev} {
        SetMode(Mode::PowerDown_HiZ);
    }

    void WriteToOutput(uint16_t RawValue) {
        uint8_t     l_byte = static_cast<uint8_t>(RawValue & 0xFF), 
                    h_byte = static_cast<uint8_t>((RawValue >> 8) & 0xFF);
        
        const std::array<uint8_t, 2> data_out = {static_cast<uint8_t>(actual_mode | h_byte), l_byte};

        spi_dev.write(data_out);
    }

    void SetMode(Mode new_mode){
        actual_mode = new_mode;
    }

 private:
    SPI::Interface& spi_dev;
    Mode actual_mode;
};

}  // namespace drivers
}  // namespace hal

#endif  // HAL_DEVICES_DAC121_H_
