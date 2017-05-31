#ifndef HAL_DEVICES_DAC1220_H_
#define HAL_DEVICES_DAC1220_H_

#include "hal/periph.h"

namespace hal {

class DAC1220 {
 public:
    enum DataLength {
        Data_20bit = 1,  //
        Data_16bit = 0
    };

    enum Mode {
        NormalMode = 0,  //
        SelfCalib  = 1,
        Sleep      = 2
    };

    enum DataOrder {
        MSB_first = 0,  //
        LSB_first = 1
    };

    enum FilterOut {
        AdaptiveFilter = 0,  //
        DefaultCuttOff = 1
    };

    enum DataFormat {
        TwosCompement = 0,  //
        Binary        = 1
    };

    enum Calibration {
        Leave = 0,  //
        Clear = 1
    };

    explicit DAC1220(SPI::Interface& spi_dev) : spi_dev{spi_dev} {
    }

    void writeToCommandReg(Calibration CRST,
                           DataLength RES,
                           DataFormat DF,
                           FilterOut DISF,
                           DataOrder MSB,
                           Mode MD) {
        uint8_t CommandRegMSB = 0;
        // ADPT
        CommandRegMSB |= (DISF << 7);
        // CALPIN
        CommandRegMSB &= ~(1 << 6);
        // CRST
        CommandRegMSB |= (CRST << 1);

        uint8_t CommandRegLSB = 0;
        // RES
        CommandRegLSB |= (RES << 7);
        // CLR
        CommandRegLSB |= (CRST << 6);
        // DF
        CommandRegLSB |= (DF << 5);
        // DISF
        CommandRegLSB |= (DISF << 4);
        // MSB
        CommandRegLSB |= (MSB << 2);
        // MD
        CommandRegLSB |= (MD << 0);

        libs::array<uint8_t, 3> arr = {0b00100100,     //
                                       CommandRegMSB,  //
                                       CommandRegLSB};
        this->spi_dev.write(arr);
    }

    void WriteToOutput(uint16_t RawValue) {
        libs::array<uint8_t, 4> arr;
        libs::Writer writer{arr};
        writer.WriteByte(0b01000000);
        writer.WriteWordLE(RawValue);
        writer.WriteByte(0);

        this->spi_dev.write(arr);
    }

 private:
    SPI::Interface& spi_dev;
};

}  // namespace hal

#endif  // HAL_DEVICES_DAC1220_H_
