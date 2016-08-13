#ifndef HAL_DEVICES_ADXRS453_H_
#define HAL_DEVICES_ADXRS453_H_

#include "SPI.h"
#include "DigitalIO.h"
#include "array.h"

namespace hal {

class ADXRS453 {
 public:
    enum RegisterMap {
        RATE = 0x00,
        TEMP = 0x02,
        LOCST = 0x04,
        HICST = 0x06,
        QUAD = 0x08,
        FAULT = 0x0A,
        PID = 0x0C,
        SN_HIGH = 0x0E,
        SN_LOW = 0x10
    };

    constexpr explicit ADXRS453(DigitalIO::Pin pin_cs) :
            spi_dev(pin_cs) {
    }

    void init() const {
        SPI::init(SPI::Polarity::idle_low, SPI::Phase::leading_sample,
                SPI::DataOrder::MSB_first, SPI::ClockDivisor::DIV_16);
        this->spi_dev.init();
    }

    bool deviceStatus() const {
        bool status = true;

        /* Read the value of the ADXRS453 ID register. */
        uint16_t sensorID = this->getRegister(RegisterMap::PID);

        if ((sensorID >> 8) != 0x52) {
            status = false;
        }

        return status;
    }

    uint32_t getSensorData() const {
        libs::array<uint8_t, 4> dataBuffer(0);

        dataBuffer[0] = (1 << 5);
        uint32_t command = (static_cast<uint32_t>(dataBuffer[0]) << 24)
                | (static_cast<uint32_t>(dataBuffer[1]) << 16)
                | (static_cast<uint32_t>(dataBuffer[2]) << 8) | dataBuffer[3];

        uint8_t sum = 0;
        for (uint8_t bitNo = 31; bitNo > 0; bitNo--) {
            sum += ((command >> bitNo) & 0x1);
        }

        if (!(sum % 2)) {
            dataBuffer[3] |= 1;
        }

        this->spi_dev.transfer(dataBuffer, dataBuffer);
        this->spi_dev.transfer(dataBuffer, dataBuffer);

        uint32_t registerValue = (static_cast<uint32_t>(dataBuffer[0]) << 24)
                | (static_cast<uint32_t>(dataBuffer[1]) << 16)
                | (static_cast<uint32_t>(dataBuffer[2]) << 8) | dataBuffer[3];

        return registerValue;
    }

    float getRate() const {
        uint16_t registerValue = this->getRegister(RegisterMap::RATE);

        /*!< If data received is in positive degree range */
        float rate = 0.0;

        if (registerValue < 0x8000) {
            rate = (static_cast<float>(registerValue) / 80);
        } else {  /*!< If data received is in negative degree range */
            rate = (-1)
                    * (static_cast<float>((0xFFFF - registerValue + 1) / 80.0));
        }

        return rate;
    }

    float getTemperature() const {
        uint16_t registerValue = getRegister(RegisterMap::TEMP);
        registerValue = (registerValue >> 6) - 0x31F;
        float temperature = static_cast<float>(registerValue) / 5;

        return temperature;
    }

 private:
    uint16_t getRegister(const uint8_t registerAddress) const {
        libs::array<uint8_t, 4> dataBuffer(0);

        dataBuffer[0] = (1 << 7) | (registerAddress >> 7);
        dataBuffer[1] = (registerAddress << 1);

        uint32_t command = (static_cast<uint32_t>(dataBuffer[0]) << 24)
                | (static_cast<uint32_t>(dataBuffer[1]) << 16)
                | (static_cast<uint32_t>(dataBuffer[2]) << 8) | dataBuffer[3];

        uint8_t sum = 0;
        for (uint8_t bitNo = 31; bitNo > 0; bitNo--) {
            sum += ((command >> bitNo) & 0x1);
        }

        if (!(sum % 2)) {
            dataBuffer[3] |= 1;
        }

        this->spi_dev.transfer(dataBuffer, dataBuffer);
        this->spi_dev.transfer(dataBuffer, dataBuffer);

        uint16_t registerValue = (static_cast<uint16_t>(dataBuffer[1]) << 11)
                | (static_cast<uint16_t>(dataBuffer[2]) << 3)
                | (dataBuffer[3] >> 5);

        return registerValue;
    }

    void setRegisterValue(const uint8_t registerAddress,
            uint16_t registerValue) const {
        libs::array<uint8_t, 4> dataBuffer(0);
        uint32_t command = 0;

        dataBuffer[0] = (1 << 6) | (registerAddress >> 7);
        dataBuffer[1] = (registerAddress << 1) | (registerValue >> 15);
        dataBuffer[2] = (registerValue >> 7);
        dataBuffer[3] = (registerValue << 1);

        command = (static_cast<uint32_t>(dataBuffer[0]) << 24)
                | (static_cast<uint32_t>(dataBuffer[1]) << 16)
                | (static_cast<uint32_t>(dataBuffer[2]) << 8) | dataBuffer[3];

        uint8_t sum = 0;
        for (uint8_t bitNo = 31; bitNo > 0; bitNo--) {
            sum += ((command >> bitNo) & 0x1);
        }

        if (!(sum % 2)) {
            dataBuffer[3] |= 1;
        }

        this->spi_dev.transmit(dataBuffer);
    }
    const SPI_Device spi_dev;
};

}  // namespace hal

#endif  // HAL_DEVICES_ADXRS453_H_
