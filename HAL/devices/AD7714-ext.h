#ifndef HAL_DEVICES_AD7714_EXT_H_
#define HAL_DEVICES_AD7714_EXT_H_

#include <util/delay.h>
#include "DigitalIO.h"
#include "SPI.h"
#include "array.h"

namespace hal {

template<typename spi>
class AD7714_ext {
 public:
    enum ADC_Registers {
        COMM_REG = 0,
        MODE_REG = 1,
        FILTER_HIGH_REG = 2,
        FILTER_LOW_REG = 3,
        TEST_REG = 4,
        DATA_REG = 5,
        ZERO_SCALE_CALIB_REG = 6,
        FULL_SCALE_CALIB_REG = 7
    };

    enum ADC_Channels {
        AIN1_CH = 0,
        AIN2_CH = 1,
        AIN3_CH = 2,
        AIN4_CH = 3,
        AIN5_CH = 6,
        AIN1_2_CH = 4,
        AIN3_4_CH = 5,
        AIN5_6_CH = 6,
        TEST_CH = 7
    };

    enum ADC_Gain {
        Gain_1 = 0,
        Gain_2 = 1,
        Gain_4 = 2,
        Gain_8 = 3,
        Gain_16 = 4,
        Gain_32 = 5,
        Gain_64 = 6,
        Gain_128 = 7
    };

    enum DataLength {
        Data_24bit = 1,  //
        Data_16bit = 0
    };

    enum ADC_Modes {
        NormalMode = 0,
        SelfCalib = 1,
        ZeroScaleSysCalib = 2,
        FullScaleSysCalib = 3,
        SysOffsetCalib = 4,
        BackgroundCalib = 5,
        ZeroScaleSelfCalib = 6,
        FullScaleSelfCalib = 7
    };

    enum Control_State {
        OFF = 0,  //
        ON = 1
    };

    enum Polarity {
        bipolar = 0,  //
        unipolar = 1
    };

    explicit AD7714_ext(DigitalIO::Pin pin_cs, DigitalIO::Pin pin_DRDY,
                        DigitalIO::Pin pin_RESET, DigitalIO::Pin pin_STANDBY,
                        DigitalIO::Pin pin_BUFFER)
        : spi_dev(pin_cs),
          pin_DRDY{pin_DRDY},
          pin_RESET{pin_RESET},
          pin_STANDBY{pin_STANDBY},
          pin_BUFFER{pin_BUFFER} {
    }

    uint8_t changeChannel(ADC_Channels channel) {
        actual_channel = channel;
        writeToCommReg(COMM_REG, true);
        this->waitForDRDY();
        return spi_dev.transfer(0);
    }

    bool data_available() {
        return (!(this->pin_DRDY.read()));
    }

    void waitForDRDY() {
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
        this->spi_dev.init();

        this->pin_DRDY.pinmode(DigitalIO::INPUT);
        this->pin_RESET.pinmode(DigitalIO::OUTPUT);
        this->pin_STANDBY.pinmode(DigitalIO::OUTPUT);
        this->pin_BUFFER.pinmode(DigitalIO::OUTPUT);

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

    void writeToCommReg(ADC_Registers reg, bool read) const {
        uint8_t out = (reg << 4) | (read << 3) | (actual_channel);
        spi_dev.transfer(out);
    }

    uint32_t read_data() {
        waitForDRDY();
        writeToCommReg(DATA_REG, true);
        spi_dev.enable();
        uint32_t tmp = spi_dev.shift(0);

        uint32_t read = 0;

        if (dataLen == Data_16bit) {
            read = (tmp << 8);
            tmp = spi_dev.shift(0);
            read |= (tmp);
        } else {
            read = (tmp << 16);
            tmp = spi_dev.shift(0);
            read |= (tmp << 8);
            tmp = spi_dev.shift(0);
            read |= (tmp);
        }

        spi_dev.disable();

        return read;
    }

    void writeToModeReg(ADC_Modes mode, ADC_Gain gain) {
        writeToCommReg(MODE_REG, false);
        uint8_t data = (mode << 5) | (gain << 2);
        spi_dev.transfer(data);
        this->waitForDRDY();
    }

    void setFilter(Polarity set_polarity, DataLength data_length,
                   uint16_t filter) {
        //  filter: 19-4000
        //  f notch = fclk/128/filter
        dataLen = data_length;
        writeToCommReg(FILTER_HIGH_REG, false);
        uint8_t val = (static_cast<bool>(set_polarity) << 7) |
                      (data_length << 6) | (1 << 5) | (filter >> 8);
        spi_dev.transfer(val);
        writeToCommReg(FILTER_LOW_REG, false);
        val = (filter & 0xFF);
        spi_dev.transfer(val);
    }

 private:
    ADC_Channels actual_channel;
    DataLength dataLen;
    const SPI::Device<spi> spi_dev;
    const DigitalIO pin_DRDY, pin_RESET, pin_STANDBY, pin_BUFFER;
};

}  // namespace hal

#endif  // HAL_DEVICES_AD7714_EXT_H_
