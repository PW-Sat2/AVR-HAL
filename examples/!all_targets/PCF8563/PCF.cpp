#include <util/delay.h>
#include "Serial.h"
#include "I2C.h"
#include "TWI.h"
#include "PCF8563.h"
#include "array.h"

constexpr hal::PCF8563<hal::TWI> rtc;

int main() {
    hal::Serial0.init(4800, hal::STDIO::ENABLE);
    printf("init! \r\n");

    hal::TWI::init<100000>();
    hal::TWI::enable_internal_pullups();
    rtc.clear_status();
    rtc.set_time(50, 52, 22);
    rtc.set_month(19, 6, 2, 17, hal::PCF8563_types::Century::Century_21st);
    rtc.set_quare_output(hal::PCF8563_types::SquareOutput::SQW_32KHZ);

    while (true) {

        hal::PCF8563_types::DateTime date_time = rtc.getDateTime();
        printf("Clock status: %d\r\n", rtc.getClockStatus());
        printf("%u:%u:%u %u-%u-%u weekday: %u clk: %u \r\n", date_time.hours, date_time.minutes, date_time.seconds, date_time.day, date_time.month, date_time.year, date_time.weekday, date_time.clk_status);
        _delay_ms(1000);
        printf("loop \r\n");
    }
}
