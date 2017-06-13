#ifndef HAL_DEVICES_ADXRS453_H_
#define HAL_DEVICES_ADXRS453_H_

#include "hal/periph.h"

namespace hal {
namespace devices {
namespace ADXRS453 {

enum RegisterMap {
    RATE    = 0x00,
    TEMP    = 0x02,
    LOCST   = 0x04,
    HICST   = 0x06,
    QUAD    = 0x08,
    FAULT   = 0x0A,
    PID     = 0x0C,
    SN_HIGH = 0x0E,
    SN_LOW  = 0x10
};

template<typename SPI>
class ADXRS453 {
 public:
    static bool device_status() {
        bool status = true;

        /* Read the value of the ADXRS453 ID register. */
        uint16_t sensorID = get_register(RegisterMap::PID);

        if ((sensorID >> 8) != 0x52) {
            status = false;
        }

        return status;
    }

    static uint32_t get_sensor_data() {
        std::array<uint8_t, 4> dataBuffer = {0, 0, 0, 0};

        dataBuffer[0]    = (1 << 5);
        uint32_t command = (static_cast<uint32_t>(dataBuffer[0]) << 24) |
                           (static_cast<uint32_t>(dataBuffer[1]) << 16) |
                           (static_cast<uint32_t>(dataBuffer[2]) << 8) |
                           dataBuffer[3];

        uint8_t sum = 0;
        for (uint8_t bitNo = 31; bitNo > 0; bitNo--) {
            sum += ((command >> bitNo) & 0x1);
        }

        if (!(sum % 2)) {
            dataBuffer[3] |= 1;
        }

        SPI::transfer(dataBuffer, dataBuffer);
        SPI::transfer(dataBuffer, dataBuffer);

        uint32_t registerValue = (static_cast<uint32_t>(dataBuffer[0]) << 24) |
                                 (static_cast<uint32_t>(dataBuffer[1]) << 16) |
                                 (static_cast<uint32_t>(dataBuffer[2]) << 8) |
                                 dataBuffer[3];

        return registerValue;
    }

    static float get_rate() {
        uint16_t registerValue = get_register(RegisterMap::RATE);

        // If data received is in positive degree range
        float rate = 0.0;

        if (registerValue < 0x8000) {
            rate = (static_cast<float>(registerValue) / 80);
        } else {
            // If data received is in negative degree range
            rate =
                (-1) * (static_cast<float>((0xFFFF - registerValue + 1) / 80.0));
        }

        return rate;
    }

    static float get_temperature() {
        uint32_t registerValue = 0;
        float temperature      = 0;
        registerValue          = get_register(RegisterMap::TEMP);

        if ((registerValue >> 6) > 0x31F) {
            registerValue = (registerValue >> 6) - 0x31F;
            temperature   = static_cast<float>(registerValue) / 5.0;
        } else {
            registerValue = (registerValue >> 6);
            temperature   = static_cast<float>(registerValue) / 5.0 + 45.0;
        }

        return temperature;
    }

 private:
    static uint16_t get_register(const uint8_t registerAddress) {
        std::array<uint8_t, 4> dataBuffer = {0, 0, 0, 0};

        dataBuffer[0] = (1 << 7) | (registerAddress >> 7);
        dataBuffer[1] = (registerAddress << 1);

        uint32_t command = (static_cast<uint32_t>(dataBuffer[0]) << 24) |
                           (static_cast<uint32_t>(dataBuffer[1]) << 16) |
                           (static_cast<uint32_t>(dataBuffer[2]) << 8) |
                           dataBuffer[3];

        uint8_t sum = 0;
        for (uint8_t bitNo = 31; bitNo > 0; bitNo--) {
            sum += ((command >> bitNo) & 0x1);
        }

        if (!(sum % 2)) {
            dataBuffer[3] |= 1;
        }

        SPI::transfer(dataBuffer, dataBuffer);
        SPI::transfer(dataBuffer, dataBuffer);

        uint16_t registerValue = (static_cast<uint16_t>(dataBuffer[1]) << 11) |
                                 (static_cast<uint16_t>(dataBuffer[2]) << 3) |
                                 (dataBuffer[3] >> 5);

        return registerValue;
    }

    static void
    set_register_value(const uint8_t registerAddress, uint16_t registerValue) {
        std::array<uint8_t, 4> dataBuffer = {0, 0, 0, 0};
        uint32_t command                  = 0;

        dataBuffer[0] = (1 << 6) | (registerAddress >> 7);
        dataBuffer[1] = (registerAddress << 1) | (registerValue >> 15);
        dataBuffer[2] = (registerValue >> 7);
        dataBuffer[3] = (registerValue << 1);

        command = (static_cast<uint32_t>(dataBuffer[0]) << 24) |
                  (static_cast<uint32_t>(dataBuffer[1]) << 16) |
                  (static_cast<uint32_t>(dataBuffer[2]) << 8) | dataBuffer[3];

        uint8_t sum = 0;
        for (uint8_t bitNo = 31; bitNo > 0; bitNo--) {
            sum += ((command >> bitNo) & 0x1);
        }

        if (!(sum % 2)) {
            dataBuffer[3] |= 1;
        }

        SPI::write(dataBuffer);
    }
};

}  // namespace ADXRS453
}  // namespace devices
}  // namespace hal

#endif  // HAL_DEVICES_ADXRS453_H_
