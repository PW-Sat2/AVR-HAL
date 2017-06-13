#ifndef HAL_DEVICES_PCF8563_H_
#define HAL_DEVICES_PCF8563_H_

#include "hal/periph.h"

namespace hal {

struct PCF8563_ {
    enum class ClockStatus {
        STOPPED = 0,
        RUNNING = 1,
    };

    enum class SquareOutput {
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
};

template<typename i2c>
class PCF8563 : public PCF8563_ {
 public:
    void clear_status() const {
        std::array<const uint8_t, 3> data = {
            Registers::CONTROL_STATUS_1, 0x00, 0x00};
        i2c::write(_addr, data);
    }

    void set_date_time(Date date, Time time) const {
        uint8_t century_years = date.year / 100;
        uint8_t month_century = dec_to_bcd(date.month);

        if (20 == century_years) {
            month_century &= ~(1 << 7);
        } else {
            month_century |= (1 << 7);
        }

        std::array<const uint8_t, 8> data = {Registers::VL_SECONDS,
                                             dec_to_bcd(time.seconds),
                                             dec_to_bcd(time.minutes),
                                             dec_to_bcd(time.hours),
                                             dec_to_bcd(date.day),
                                             dec_to_bcd(date.weekday),
                                             month_century,
                                             dec_to_bcd(date.year % 100)};

        i2c::write(_addr, data);
    }

    void set_square_output(SquareOutput frequency) const {
        std::array<const uint8_t, 2> data = {Registers::CLKOUT_CTRL,
                                             static_cast<uint8_t>(frequency)};
        i2c::write(_addr, data);
    }

    ClockStatus get_date_time(Date& date, Time& time) const {
        std::array<uint8_t, 1> tx = {Registers::VL_SECONDS};
        std::array<uint8_t, 7> data;
        i2c::write_read(_addr, tx, data);

        time.hours   = bcdToDec(data[2] & 0x3F);
        time.minutes = bcdToDec(data[1] & 0x7F);
        time.seconds = bcdToDec(data[0] & 0x7F);

        date.day     = bcdToDec(data[3] & 0x3F);
        date.weekday = bcdToDec(data[4] & 0x07);
        date.month   = bcdToDec(data[5] & 0x1F);

        if (data[5] & 0x80) {
            date.year = 1900 + bcdToDec(data[6]);
        } else {
            date.year = 2000 + bcdToDec(data[6]);
        }

        if (data[0] & 0x80) {
            return ClockStatus::STOPPED;
        } else {
            return ClockStatus::RUNNING;
        }
    }

    ClockStatus get_clock_status() const {
        std::array<uint8_t, 1> tx = {Registers::VL_SECONDS};
        std::array<uint8_t, 1> data;
        i2c::write_read(_addr, tx, data);

        if (data[0] & 0x80) {
            return ClockStatus::STOPPED;
        } else {
            return ClockStatus::RUNNING;
        }
    }

 private:
    enum Registers {
        CONTROL_STATUS_1 = 0x00,
        CONTROL_STATUS_2 = 0x01,
        VL_SECONDS       = 0x02,
        MINUTES          = 0x03,
        HOURS            = 0x04,
        DAYS             = 0x05,
        WEEKDAYS         = 0x06,
        CENTURY_MONTHS   = 0x07,
        YEARS            = 0x08,
        MINUTE_ALARM     = 0x09,
        HOUR_ALARM       = 0x0A,
        DAY_ALARM        = 0x0B,
        WEEKDAY_ALARM    = 0x0C,
        CLKOUT_CTRL      = 0x0D,
        TIMER_CTRL       = 0x0E,
        TIMER            = 0x0F,
    };

    I2C::Interface::Address _addr = 0x51;

    uint8_t dec_to_bcd(uint8_t val) const {
        return ((val / 10 * 16) + (val % 10));
    }

    uint8_t bcdToDec(uint8_t val) const {
        return ((val / 16 * 10) + (val % 16));
    }
};

}  // namespace hal

#endif  // HAL_DEVICES_PCF8563_H_
