#ifndef HAL_DEVICES_AD7714_EXT_H_
#define HAL_DEVICES_AD7714_EXT_H_

#include "hal/libs.h"
#include "hal/periph.h"

namespace hal {
namespace devices {
namespace AD7714_ext {

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

enum class DataLength : std::uint8_t {
    d24bit = 1,  //
    d16bit = 0
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

enum class ControlState : std::uint8_t {
    OFF = 0,  //
    ON  = 1
};

enum class Polarity : std::uint8_t {
    bipolar  = 0,  //
    unipolar = 1
};

template<typename SPI, typename pin_DRDY, typename pin_RESET, typename pin_STANDBY, typename pin_BUFFER>
class AD7714_ext {
 public:
    void init() const {
        pin_DRDY::init(DigitalIO::Mode::INPUT);
        pin_RESET::init(DigitalIO::Mode::OUTPUT);
        pin_STANDBY::init(DigitalIO::Mode::OUTPUT);
        pin_BUFFER::init(DigitalIO::Mode::OUTPUT);

        this->reset();
        this->buffer(ControlState::ON);
        this->power_mode(ControlState::OFF);
    }

    void power_mode(ControlState status) const {
        pin_STANDBY::write(static_cast<bool>(status));
        _delay_ms(10);
    }

    void buffer(ControlState buff_stat) const {
        pin_BUFFER::write(static_cast<bool>(buff_stat));
    }

    uint8_t change_channel(Channels channel) {
        actual_channel = channel;
        write_to_comm_reg(Registers::COMM_REG, true);
        wait_for_DRDY();
        return SPI::transfer(0);
    }
    uint32_t read_data() {
        wait_for_DRDY();
        write_to_comm_reg(Registers::DATA_REG, true);

        if (data_length == DataLength::d16bit) {
            std::array<uint8_t, 2> data;
            SPI::read(data);
            libs::Reader reader{data};
            return reader.ReadWordBE();
        } else {  // data_length == Data_24bit
            std::array<uint8_t, 3> data;
            SPI::read(data);

            uint32_t read = 0;
            read |= data[0], read <<= 8;
            read |= data[1], read <<= 8;
            read |= data[2];

            return read;
        }
    }

    void
    set_filter(Polarity set_polarity, DataLength data_length, uint16_t filter) {
        //  filter: 19-4000
        //  f notch = fclk/128/filter
        data_length = data_length;
        write_to_comm_reg(Registers::FILTER_HIGH_REG, false);
        uint8_t val = (static_cast<bool>(set_polarity) << 7) |    //
                      (static_cast<uint8_t>(data_length) << 6) |  //
                      (1 << 5) |                                  //
                      (filter >> 8);
        SPI::transfer(val);
        write_to_comm_reg(Registers::FILTER_LOW_REG, false);
        val = (filter & 0xFF);
        SPI::transfer(val);
    }

 private:
    Channels actual_channel;
    DataLength data_length;

    void wait_for_DRDY() {
        while (pin_DRDY::read()) {
        }
    }

    void reset() const {
        pin_RESET::reset();
        _delay_ms(10);
        pin_RESET::set();
        _delay_ms(10);
    }

    void write_to_comm_reg(Registers reg, bool read) const {
        uint8_t out = (static_cast<uint8_t>(reg) << 4) |  //
                      (read << 3) |                       //
                      static_cast<uint8_t>(actual_channel);
        SPI::transfer(out);
    }


    void writeto_mode_reg(Modes mode, Gain gain) {
        write_to_comm_reg(Registers::MODE_REG, false);
        uint8_t data = (static_cast<uint8_t>(mode) << 5) |  //
                       (static_cast<uint8_t>(gain) << 2);   //
        SPI::transfer(data);
        this->wait_for_DRDY();
    }
};

}  // namespace AD7714_ext
}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_AD7714_EXT_H_
