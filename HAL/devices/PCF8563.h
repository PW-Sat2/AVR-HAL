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

enum SquareOutput {
    SQW_DISABLE = 0b00000000,
    SQW_32KHZ = 0b10000000,
    SQW_1024HZ = 0b10000001,
    SQW_32HZ = 0b10000010,
    SQW_1HZ = 0b10000011
};

struct Time {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
};

struct Date {
    uint8_t day;
    uint8_t weekday;
    uint8_t month;
    uint16_t year;
};

}  // namespace PCF8563_types

template<typename I2C>
class PCF8563 {
 public:
    void clear_status() const {
        libs::array<const uint8_t, 2> data = {0x00, 0x00};
        i2cdevice.write_register(PCF8563_types::Registers::CONTROL_STATUS_1, data);
    }

    void set_date_time(PCF8563_types::Date date, PCF8563_types::Time time) const {
        uint8_t century_years = date.year/100;
        uint8_t month_century = decToBcd(date.month);

        if (20 == century_years) {
            month_century &= ~(1 << 7);
        } else {
            month_century |= (1 << 7);
        }

        libs::array<const uint8_t, 7> data = {
            decToBcd(time.seconds),
            decToBcd(time.minutes),
            decToBcd(time.hours),
            decToBcd(date.day),
            decToBcd(date.weekday),
            month_century,
            decToBcd(date.year%100)
        };

        i2cdevice.write_register(PCF8563_types::Registers::VL_SECONDS, data);
    }

    void set_square_output(PCF8563_types::SquareOutput frequency) const {
        libs::array<const uint8_t, 1> data = {frequency};
        i2cdevice.write_register(PCF8563_types::Registers::CLKOUT_CTRL, data);
    }

    PCF8563_types::ClockStatus get_date_time(PCF8563_types::Date &date, PCF8563_types::Time &time) const {
        libs::array<uint8_t, 7> data;
        i2cdevice.read_register(PCF8563_types::Registers::VL_SECONDS, data);

        time.hours = bcdToDec(data[2] & 0x3F);
        time.minutes = bcdToDec(data[1] & 0x7F);
        time.seconds = bcdToDec(data[0] & 0x7F);

        date.day = bcdToDec(data[3] & 0x3F);
        date.weekday = bcdToDec(data[4] & 0x07);
        date.month = bcdToDec(data[5] & 0x1F);

        if (data[5] & 0x80) {
            date.year = 1900 + bcdToDec(data[6]);
        } else {
            date.year = 2000 + bcdToDec(data[6]);
        }

        if (data[0] & 0x80) {
            return PCF8563_types::ClockStatus::STOPPED;
        } else {
            return PCF8563_types::ClockStatus::RUNNING;
        }
    }

    PCF8563_types::ClockStatus getClockStatus() const {
        libs::array<uint8_t, 1> data;
        i2cdevice.read_register(PCF8563_types::Registers::VL_SECONDS, data);

        if (data[0] & 0x80) {
            return PCF8563_types::ClockStatus::STOPPED;
        } else {
            return PCF8563_types::ClockStatus::RUNNING;
        }
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
