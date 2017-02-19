#ifndef HAL_DEVICES_PCF8563_H_
#define HAL_DEVICES_PCF8563_H_

#include <stdlib.h>
#include "I2C.h"
#include "array.h"
#include "array_view.h"

namespace hal {

namespace PCF8563_types {

enum Registers {
    CONTROL_STATUS_1 = 0x00,
    CONTROL_STATUS_2 = 0x01,
    VL_SECONDS = 0x02,
    MINUTES = 0x03,
    HOURS = 0x04,
    DAYS = 0x05,
    WEEKDAYS = 0x06,
    CENTURY_MONTHS = 0x07,
    YEARS = 0x08,
    MINUTE_ALARM = 0x09,
    HOUR_ALARM = 0x0A,
    DAY_ALARM = 0x0B,
    WEEKDAY_ALARM = 0x0C,
    CLKOUT_CTRL = 0x0D,
    TIMER_CTRL = 0x0E,
    TIMER = 0x0F
};

enum ClockStatus {
    STOPPED = 0,
    RUNNING = 1
};

enum Century {
    Century_21st = 0x00,
    Century_20th = 0x01
};

enum SquareOutput {
    SQW_DISABLE = 0b00000000,
    SQW_32KHZ = 0b10000000,
    SQW_1024HZ = 0b10000001,
    SQW_32HZ = 0b10000010,
    SQW_1HZ = 0b10000011
};

struct DateTime {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t day;
    uint8_t weekday;
    uint8_t month;
    uint16_t year;
    bool clk_status;
};

}  // namespace PCF8563_types

template<typename I2C>
class PCF8563 {
 public:
    void clear_status() const {
        libs::array<const uint8_t, 2> data = {0x00, 0x00};
        i2cdevice.write_register(PCF8563_types::Registers::CONTROL_STATUS_1, data);
    }

    void set_time(const uint8_t seconds, const uint8_t minutes, const uint8_t hours) const {
        libs::array<const uint8_t, 3> data = {decToBcd(seconds), decToBcd(minutes), decToBcd(hours)};
        i2cdevice.write_register(PCF8563_types::Registers::VL_SECONDS, data);
    }

    void set_month(const uint8_t day, const uint8_t weekday, const uint8_t month, const uint8_t year,
         const PCF8563_types::Century century) const {
        uint8_t month_century = decToBcd(month);

        if (PCF8563_types::Century::Century_21st == century) {
            month_century &= ~(0x80);
        } else {
            month_century |= 0x80;
        }

        libs::array<const uint8_t, 4> data = {decToBcd(day), decToBcd(weekday), month_century, decToBcd(year)};
        i2cdevice.write_register(PCF8563_types::Registers::DAYS, data);
    }

    void set_quare_output(PCF8563_types::SquareOutput frequency) const {
        libs::array<const uint8_t, 1> data = {frequency};
        i2cdevice.write_register(PCF8563_types::Registers::CLKOUT_CTRL, data);
    }

    PCF8563_types::DateTime getDateTime() const {
        libs::array<uint8_t, 7> data;
        i2cdevice.read_register(PCF8563_types::Registers::VL_SECONDS, data);

        PCF8563_types::DateTime datetime;

        datetime.hours = bcdToDec(data[2] & 0x3f);
        datetime.minutes = bcdToDec(data[1] & 0x7f);
        datetime.seconds = bcdToDec(data[0] & 0x7f);


        datetime.day = bcdToDec(data[3] & 0x3F);
        datetime.weekday = bcdToDec(data[4] & 0x07);
        datetime.month = bcdToDec(data[5] & 0x1f);

        if (data[5] & 0x80) {
            datetime.year = 1900 + bcdToDec(data[6]);
        } else {
            datetime.year = 2000 + bcdToDec(data[6]);
        }

        if (true == static_cast<bool>(data[0] & 0x80)) {
            datetime.clk_status = PCF8563_types::ClockStatus::STOPPED;
        } else {
            datetime.clk_status = PCF8563_types::ClockStatus::RUNNING;
        }

        return datetime;
    }

    PCF8563_types::ClockStatus getClockStatus() const {
        libs::array<uint8_t, 1> data;
        i2cdevice.read_register(PCF8563_types::Registers::VL_SECONDS, data);

        PCF8563_types::ClockStatus status;

        if (true == static_cast<bool>(data[0] & 0x80)) {
            status = PCF8563_types::ClockStatus::STOPPED;
        } else {
            status = PCF8563_types::ClockStatus::RUNNING;
        }

        return status;
    }


 private:
    const I2C_Device<I2C> i2cdevice{0x51};

    uint8_t decToBcd(uint8_t val) const {
        return ((val/10*16) + (val%10));
    }

    uint8_t bcdToDec(uint8_t val) const {
        return ((val/16*10) + (val%16));
    }
};

}  // namespace hal

#endif  // HAL_DEVICES_PCF8563_H_
