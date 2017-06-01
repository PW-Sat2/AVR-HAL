#ifndef HAL_DEVICES_AD7714_H_
#define HAL_DEVICES_AD7714_H_

#include "hal/periph.h"

namespace hal {

class AD7714 {
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

    enum DataLength { Data_24bit = 1 };

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


    explicit AD7714(SPI::Interface& spi, DigitalIO::Interface& pin_DRDY)
        : spi_dev(spi), pin_DRDY{pin_DRDY} {
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


    void init() const {
        this->pin_DRDY.init(DigitalIO::Interface::Mode::INPUT);
    }

    void writeToCommReg(ADC_Registers reg, bool read) const {
        uint8_t out = (reg << 4) | (read << 3) | (actual_channel);
        spi_dev.transfer(out);
    }


    uint32_t read_data() {
        waitForDRDY();
        writeToCommReg(DATA_REG, true);

        std::array<uint8_t, 3> data;
        spi_dev.read(data);

        uint32_t read = 0;
        read |= data[0], read <<= 8;
        read |= data[1], read <<= 8;
        read |= data[2];

        return read;
    }


    void writeToModeReg(ADC_Modes mode, ADC_Gain gain) {
        writeToCommReg(MODE_REG, false);
        uint8_t data = (mode << 5) | (gain << 2);
        spi_dev.transfer(data);
        this->waitForDRDY();
    }


    void setFilter(Polarity set_polarity, uint16_t filter) {
        //  filter: 19-4000
        //  f notch = fclk/128/filter
        writeToCommReg(FILTER_HIGH_REG, false);
        uint8_t val = (static_cast<bool>(set_polarity) << 7) |  //
                      (DataLength::Data_24bit << 6) |           //
                      (1 << 5) |                                //
                      (filter >> 8);
        spi_dev.transfer(val);
        writeToCommReg(FILTER_LOW_REG, false);
        val = (filter & 0xFF);
        spi_dev.transfer(val);
    }

 private:
    ADC_Channels actual_channel;

    SPI::Interface& spi_dev;
    DigitalIO::Interface& pin_DRDY;
};

}  // namespace hal

#endif  // HAL_DEVICES_AD7714_H_
