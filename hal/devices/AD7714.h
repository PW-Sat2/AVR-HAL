#ifndef HAL_DEVICES_AD7714_H_
#define HAL_DEVICES_AD7714_H_

#include <hal/hal>
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

template<typename spi_dev, typename pin_DRDY>
class AD7714 {
 public:
    void change_channel(Channels channel) {
        this->actual_channel = channel;
        write_to_comm_reg(Registers::COMM_REG, true);

        std::uint8_t data;
        spi_dev::read(data);
    }


    void init() const {
        pin_DRDY::init(DigitalIO::Mode::INPUT);
    }


    uint24_t read_data_no_wait() {
        write_to_comm_reg(Registers::DATA_REG, true);

        uint32_t read = 0;
        std::array<std::uint8_t, 3> data;
        spi_dev::read(data);
        read = (static_cast<uint32_t>(data[0]) << 16);
        read |= (static_cast<uint32_t>(data[1]) << 8);
        read |= (static_cast<uint32_t>(data[2]));
        return static_cast<uint24_t>(read);
    }

    uint24_t read_data() {
        this->wait_for_DRDY();
        return this->read_data_no_wait();
    }


    void set_mode(Modes mode, Gain gain) {
        write_to_comm_reg(Registers::MODE_REG, false);
        std::uint8_t data = (static_cast<std::uint8_t>(mode) << 5) |
                            (static_cast<std::uint8_t>(gain) << 2);
        spi_dev::write(data);
    }


    void set_filter(Polarity set_polarity, uint16_t filter) {
        //  filter: 19-4000
        //  f notch = fclk/128/filter
        write_to_comm_reg(Registers::FILTER_HIGH_REG, false);
        std::uint8_t val = (static_cast<std::uint8_t>(set_polarity) << 7) |
                           (1 << 6) | (1 << 5) |
                           libs::read_mask<7, 4>(static_cast<uint16_t>(filter));
        spi_dev::write(val);

        write_to_comm_reg(Registers::FILTER_LOW_REG, false);
        val = libs::read_mask<0, 8>(static_cast<std::uint8_t>(filter));
        spi_dev::write(val);
    }

    bool data_ready() {
        return !pin_DRDY::read();
    }

 private:
    Channels actual_channel;

    void wait_for_DRDY() {
        while (pin_DRDY::read()) {
        }
    }

    void write_to_comm_reg(Registers reg, bool read) const {
        std::uint8_t out = (static_cast<std::uint8_t>(reg) << 4) |
                           (static_cast<std::uint8_t>(read) << 3) |
                           (static_cast<std::uint8_t>(actual_channel));
        spi_dev::write(out);
    }
};

}  // namespace AD7714
}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_AD7714_H_
