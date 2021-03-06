#include <hal/hal>

using namespace std::chrono_literals;
using hal::Serial0;
using namespace hal::devices;

int main() {
    Serial0.init(115200);
    Serial0.redirect_stdio();
    Serial0.redirect_stderr();

    using pin_sda = hal::DigitalIO::GPIO<hal::mcu::pin_sda>;
    using pin_scl = hal::DigitalIO::GPIO<hal::mcu::pin_scl>;

    using i2c = hal::I2C::Software<pin_sda, pin_scl>;
    i2c::init();

    using rtc = PCF8563::PCF8563<i2c>;

    if (PCF8563::ClockStatus::STOPPED == rtc::get_clock_status()) {
        printf("Clock is not working, setting time!\r\n");
        rtc::clear_status();
        rtc::set_date_time({20, 1, 2, 1994}, {20, 00, 00});
    } else {
        printf("RTC is working!\r\n");
    }

    rtc::set_square_output(PCF8563::SquareOutput::SQW_32KHZ);
    PCF8563::Date date;
    PCF8563::Time time;

    while (true) {
        if (PCF8563::ClockStatus::RUNNING == rtc::get_date_time(date, time)) {
            printf("%02u:%02u:%02u\t%02u-%02u-%4u weekday: %u\r\n",
                   time.hours,
                   time.minutes,
                   time.seconds,
                   date.day,
                   date.month,
                   date.year,
                   date.weekday);
        } else {
            printf("RTC clock is not working...\r\n");
        }
        hal::sleep_for(1000ms);
    }
}
