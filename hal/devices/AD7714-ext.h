#ifndef HAL_DEVICES_AD7714_EXT_H_
#define HAL_DEVICES_AD7714_EXT_H_

#include "hal/libs.h"
#include "hal/periph.h"

namespace hal {

class AD7714_ext {
 public:
    enum ADC_Registers {
        COMM_REG             = 0,
        MODE_REG             = 1,
        FILTER_HIGH_REG      = 2,
        FILTER_LOW_REG       = 3,
        TEST_REG             = 4,
        DATA_REG             = 5,
        ZERO_SCALE_CALIB_REG = 6,
        FULL_SCALE_CALIB_REG = 7
    };

    enum ADC_Channels {
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

    enum ADC_Gain {
        Gain_1   = 0,
        Gain_2   = 1,
        Gain_4   = 2,
        Gain_8   = 3,
        Gain_16  = 4,
        Gain_32  = 5,
        Gain_64  = 6,
        Gain_128 = 7
    };

    enum DataLength {
        Data_24bit = 1,  //
        Data_16bit = 0
    };

    enum ADC_Modes {
        NormalMode         = 0,
        SelfCalib          = 1,
        ZeroScaleSysCalib  = 2,
        FullScaleSysCalib  = 3,
        SysOffsetCalib     = 4,
        BackgroundCalib    = 5,
        ZeroScaleSelfCalib = 6,
        FullScaleSelfCalib = 7
    };

    enum Control_State {
        OFF = 0,  //
        ON  = 1
    };

    enum Polarity {
        bipolar  = 0,  //
        unipolar = 1
    };

    explicit AD7714_ext(SPI::Interface& spi_dev,
                        DigitalIO::Interface& pin_DRDY,
                        DigitalIO::Interface& pin_RESET,
                        DigitalIO::Interface& pin_STANDBY,
                        DigitalIO::Interface& pin_BUFFER)
        : spi_dev(spi_dev),
          pin_DRDY{pin_DRDY},
          pin_RESET{pin_RESET},
          pin_STANDBY{pin_STANDBY},
          pin_BUFFER{pin_BUFFER} {
    }

    uint8_t change_channel(ADC_Channels channel) {
        actual_channel = channel;
        write_to_comm_reg(COMM_REG, true);
        this->wait_for_DRDY();
        return spi_dev.transfer(0);
    }

    bool data_available() {
        return (!(this->pin_DRDY.read()));
    }

    void wait_for_DRDY() {
        while (!data_available()) {
        }
    }

    void reset() const {
        this->pin_RESET.reset();
        _delay_ms(10);
        this->pin_RESET.set();
        _delay_ms(10);
    }

    void init() const {
        this->pin_DRDY.init(DigitalIO::Interface::Mode::INPUT);
        this->pin_RESET.init(DigitalIO::Interface::Mode::OUTPUT);
        this->pin_STANDBY.init(DigitalIO::Interface::Mode::OUTPUT);
        this->pin_BUFFER.init(DigitalIO::Interface::Mode::OUTPUT);

        this->reset();
        this->buffer(ON);
        this->power_mode(OFF);
    }

    void power_mode(Control_State status) const {
        pin_STANDBY.write(static_cast<bool>(status));
        _delay_ms(10);
    }

    void buffer(Control_State buff_stat) const {
        pin_BUFFER.write(static_cast<bool>(buff_stat));
    }

    void write_to_comm_reg(ADC_Registers reg, bool read) const {
        uint8_t out = (reg << 4) | (read << 3) | (actual_channel);
        spi_dev.transfer(out);
    }

    uint32_t read_data() {
        wait_for_DRDY();
        write_to_comm_reg(DATA_REG, true);

        if (data_length == Data_16bit) {
            std::array<uint8_t, 2> data;
            spi_dev.read(data);
            libs::Reader reader{data};
            return reader.ReadWordBE();
        } else {  // data_length == Data_24bit
            std::array<uint8_t, 3> data;
            spi_dev.read(data);

            uint32_t read = 0;
            read |= data[0], read <<= 8;
            read |= data[1], read <<= 8;
            read |= data[2];

            return read;
        }
    }

    void writeto_mode_reg(ADC_Modes mode, ADC_Gain gain) {
        write_to_comm_reg(MODE_REG, false);
        uint8_t data = (mode << 5) | (gain << 2);
        spi_dev.transfer(data);
        this->wait_for_DRDY();
    }

    void
    set_filter(Polarity set_polarity, DataLength data_length, uint16_t filter) {
        //  filter: 19-4000
        //  f notch = fclk/128/filter
        data_length = data_length;
        write_to_comm_reg(FILTER_HIGH_REG, false);
        uint8_t val = (static_cast<bool>(set_polarity) << 7) |
                      (data_length << 6) | (1 << 5) | (filter >> 8);
        spi_dev.transfer(val);
        write_to_comm_reg(FILTER_LOW_REG, false);
        val = (filter & 0xFF);
        spi_dev.transfer(val);
    }

 private:
    ADC_Channels actual_channel;
    DataLength data_length;
    SPI::Interface& spi_dev;
    DigitalIO::Interface &pin_DRDY, &pin_RESET, &pin_STANDBY, &pin_BUFFER;
};

}  // namespace hal

#endif  // HAL_DEVICES_AD7714_EXT_H_
