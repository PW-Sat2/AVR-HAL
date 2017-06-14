#ifndef HAL_DEVICES_AD7714_H_
#define HAL_DEVICES_AD7714_H_

#include "hal/periph.h"

namespace hal {
namespace devices {
namespace AD7714 {

enum class Registers : std::uint8_t {
    COMM_REG             = 0,
    MODE_REG             = 1,
    FILTER_HIGH_REG      = 2,
    FILTER_LOW_REG       = 3,
    TEST_REG             = 4,
    DATA_REG             = 5,
    ZERO_SCALE_CALIB_REG = 6,
    FULL_SCALE_CALIB_REG = 7
};

enum class Channels : std::uint8_t {
    AIN1_CH   = 0,
    AIN2_CH   = 1,
    AIN3_CH   = 2,
    AIN4_CH   = 3,
    AIN5_CH   = 6,
    AIN1_2_CH = 4,
    AIN3_4_CH = 5,
    AIN5_6_CH = 6,
    TEST_CH   = 7
};

enum class Gain : std::uint8_t {
    Gain_1   = 0,
    Gain_2   = 1,
    Gain_4   = 2,
    Gain_8   = 3,
    Gain_16  = 4,
    Gain_32  = 5,
    Gain_64  = 6,
    Gain_128 = 7
};

enum class Modes : std::uint8_t {
    NormalMode         = 0,
    SelfCalib          = 1,
    ZeroScaleSysCalib  = 2,
    FullScaleSysCalib  = 3,
    SysOffsetCalib     = 4,
    BackgroundCalib    = 5,
    ZeroScaleSelfCalib = 6,
    FullScaleSelfCalib = 7
};

enum class Control_State : std::uint8_t {
    OFF = 0,  //
    ON  = 1
};

enum class Polarity : std::uint8_t {
    bipolar  = 0,  //
    unipolar = 1
};

template<typename SPI, typename pin_DRDY>
class AD7714 {
 public:
    uint8_t change_channel(Channels channel) {
        actual_channel = channel;
        write_to_comm_reg(Registers::COMM_REG, true);
        this->wait_for_DRDY();
        return SPI::transfer(0);
    }


    void init() const {
        pin_DRDY::init(DigitalIO::Mode::INPUT);
    }

    uint24_t read_data() {
        wait_for_DRDY();
        write_to_comm_reg(Registers::DATA_REG, true);

        std::array<uint8_t, 3> data;
        SPI::read(data);

        uint24_t read = 0;
        read |= data[0], read <<= 8;
        read |= data[1], read <<= 8;
        read |= data[2];

        return read;
    }

    void set_filter(Polarity polarity, uint16_t filter) {
        //  filter: 19-4000
        //  f notch = fclk/128/filter
        write_to_comm_reg(Registers::FILTER_HIGH_REG, false);
        uint8_t val = (static_cast<std::uint8_t>(polarity) << 7) |  //
                      (1 << 6) |                                    //
                      (1 << 5) |                                    //
                      (filter >> 8);
        SPI::transfer(val);
        write_to_comm_reg(Registers::FILTER_LOW_REG, false);
        val = (filter & 0xFF);
        SPI::transfer(val);
    }

 private:
    Channels actual_channel;

    void wait_for_DRDY() {
        while (pin_DRDY::read()) {
        }
    }

    void write_to_comm_reg(Registers reg, bool read) const {
        uint8_t out = (num(reg) << 4) |  //
                      (read << 3) |      //
                      num(actual_channel);
        SPI::transfer(out);
    }

    void writeto_(Modes mode, Gain gain) {
        write_to_comm_reg(Registers::MODE_REG, false);
        uint8_t data = (num(mode) << 5) | (num(gain) << 2);
        SPI::transfer(data);
        this->wait_for_DRDY();
    }
};

}  // namespace AD7714
}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_AD7714_H_
