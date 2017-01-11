#ifndef HAL_DEVICES_DAC1220_H_
#define HAL_DEVICES_DAC1220_H_

#include <util/delay.h>
#include "DigitalIO.h"
#include "SPI.h"
#include "array.h"

namespace hal {

class DAC1220 {
 public:
    enum DataLength {
        Data_20bit = 1,  //
        Data_16bit = 0
    };

    enum Mode {
        NormalMode = 0,  //
        SelfCalib = 1,
        Sleep = 2
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
        Binary = 1
    };

    enum Calibration {
        Leave = 0,  //
        Clear = 1
    };

    explicit DAC1220(DigitalIO::Pin pin_cs) : spi_dev(pin_cs) {
    }

    void init() const {
        this->spi_dev.init();
        this->spi_dev.disable();
    }

    void writeToCommandReg(Calibration CRST, DataLength RES, DataFormat DF,
                           FilterOut DISF, DataOrder MSB, Mode MD) {
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

        this->spi_dev.enable();
        // write two bytes to command register
        this->spi_dev.shift(0b00100100);
        this->spi_dev.shift(CommandRegMSB);
        this->spi_dev.shift(CommandRegLSB);
        this->spi_dev.disable();
    }

    void WriteToOutput(uint16_t RawValue) {
        this->spi_dev.enable();
        // write to output registers
        this->spi_dev.shift(0b01000000);

        // write raw data
        this->spi_dev.shift(static_cast<uint8_t>(RawValue >> 8));
        this->spi_dev.shift(static_cast<uint8_t>(RawValue & 0x00FF));
        this->spi_dev.shift(0x00);
        this->spi_dev.disable();
    }

 private:
    const SPI_Device spi_dev;
};

}  // namespace hal

#endif  // HAL_DEVICES_DAC1220_H_
