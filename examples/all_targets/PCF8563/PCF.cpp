#include <hal/hal>

int main() {
    hal::Serial0.init(4800, hal::STDIO::ENABLE);

    hal::DigitalIO::GPIO<hal::mcu::pin_sda> pin_sda;
    hal::DigitalIO::GPIO<hal::mcu::pin_scl> pin_scl;

    hal::I2C::Software i2c{pin_sda, pin_scl};
    i2c.init();

    hal::PCF8563 rtc{i2c};


    if (hal::PCF8563::ClockStatus::STOPPED == rtc.getClockStatus()) {
        printf("Clock is not working, setting time!\r\n");
        rtc.clear_status();
        rtc.set_date_time({20, 1, 2, 1994}, {20, 00, 00});
    } else {
        printf("RTC is working!\r\n");
    }

    rtc.set_square_output(hal::PCF8563::SquareOutput::SQW_32KHZ);
    hal::PCF8563::Date date;
    hal::PCF8563::Time time;

    while (true) {
        if (hal::PCF8563::ClockStatus::RUNNING == rtc.get_date_time(date, time)) {
            printf("%02u:%02u:%02u\t%02u-%02u-%4u weekday: %u\r\n",
                time.hours, time.minutes, time.seconds,
                date.day, date.month, date.year, date.weekday);
        } else {
            printf("RTC clock is not working...\r\n");
        }
        _delay_ms(1000);
    }
}
