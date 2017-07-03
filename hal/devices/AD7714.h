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
    FULL_SCALE_CALIB_REG = 7,
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
    TEST_CH   = 7,
};

enum class Gain : std::uint8_t {
    GAIN_1   = 0,
    GAIN_2   = 1,
    GAIN_4   = 2,
    GAIN_8   = 3,
    GAIN_16  = 4,
    GAIN_32  = 5,
    GAIN_64  = 6,
    GAIN_128 = 7,
};

enum class Modes : std::uint8_t {
    NORMAL_MODE           = 0,
    SELF_CALIB            = 1,
    ZERO_SCALE_SYS_CALIB  = 2,
    FULL_SCALE_SYS_CALIB  = 3,
    SYS_OFFSET_CALIB      = 4,
    BACKGROUND_CALIB      = 5,
    ZERO_SCALE_SELF_CALIB = 6,
    FULL_SCALE_SELF_CALIB = 7,
};

enum class Polarity : std::uint8_t {
    BIPOLAR  = 0,
    UNIPOLAR = 1,
};

template<typename SPI, typename pin_DRDY>
class AD7714 {
 public:
    void init() const {
        pin_DRDY::init(DigitalIO::Mode::INPUT);
    }


    void change_channel(Channels channel) {
        this->actual_channel = channel;
        std::uint8_t data;
        this->read_register(Registers::COMM_REG, data);
    }


    template<std::uint16_t filter>
    void set_filter(const Polarity set_polarity) {
        static_assert((filter >= 19) && (filter <= 4000),
                      "Allowed filter value is 19 - 4000");

        std::uint8_t val = (num(set_polarity) << 7) |
                           (this->word_len_24b << 6) | (filter >> 8);
        this->write_register(Registers::FILTER_HIGH_REG, val);

        val = libs::read_mask<0, 8>(filter);
        this->write_register(Registers::FILTER_LOW_REG, val);
    }


    void set_mode(const Modes mode, const Gain gain) {
        std::uint8_t data = (num(mode) << 5) | (num(gain) << 2);
        this->write_register(Registers::MODE_REG, data);
    }


    bool data_ready() {
        return !pin_DRDY::read();
    }


    uint24_t read_data_no_wait() {
        std::array<std::uint8_t, 3> data;
        this->read_register(Registers::DATA_REG, data);

        std::uint32_t read = 0;
        read |= data[0], read <<= 8;
        read |= data[1], read <<= 8;
        read |= data[2];
        return static_cast<uint24_t>(read);
    }

 private:
    Channels actual_channel;
    constexpr static bool word_len_24b = true;

    template<typename T>
    void read_register(const Registers reg, T& data) const {
        std::uint8_t out = (num(reg) << 4) | (1 << 3) | (num(actual_channel));
        SPI::write(out);
        SPI::read(data);
    }

    template<typename T>
    void write_register(const Registers reg, T& data) const {
        std::uint8_t out = (num(reg) << 4) | (num(actual_channel));
        SPI::write(out);
        SPI::write(data);
    }
};

}  // namespace AD7714
}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_AD7714_H_
