#include <util/delay.h>
#include "Serial.h"
#include "I2C.h"
#include "SoftI2C.h"
#include "PCF8563.h"
#include "array.h"

int main() {
    hal::Serial0.init(4800, hal::STDIO::ENABLE);

    using SoftI2C = hal::SoftI2C<hal::mcu::pin_sda, hal::mcu::pin_scl>;
    using PCF8563 = hal::PCF8563<SoftI2C>;
    SoftI2C::init();
    constexpr PCF8563 rtc;

    if (PCF8563::ClockStatus::STOPPED == rtc.getClockStatus()) {
        printf("Clock is not working, setting time!\r\n");
        rtc.clear_status();
        rtc.set_date_time({20, 1, 2, 1994}, {20, 00, 00});
    } else {
        printf("RTC is working!\r\n");
    }

    rtc.set_square_output(PCF8563::SquareOutput::SQW_32KHZ);
    PCF8563::Date date;
    PCF8563::Time time;

    while (true) {
        if (PCF8563::ClockStatus::RUNNING == rtc.get_date_time(date, time)) {
            printf("%02u:%02u:%02u\t%02u-%02u-%4u weekday: %u\r\n",
                time.hours, time.minutes, time.seconds,
                date.day, date.month, date.year, date.weekday);
        } else {
            printf("RTC clock is not working...\r\n");
        }
        _delay_ms(1000);
    }
}
