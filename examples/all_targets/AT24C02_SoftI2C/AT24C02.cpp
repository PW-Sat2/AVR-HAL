#include <util/delay.h>
#include "Serial.h"
#include "I2C.h"
#include "TWI.h"
#include "AT24C02.h"
#include "array.h"

#include "SoftI2C.h"

using softI2C_1 = hal::SoftI2C<hal::mcu::pin_sda, hal::mcu::pin_scl>;
constexpr hal::AT24C02<softI2C_1> memory;

int main() {
    hal::Serial0.init(115200, hal::STDIO::ENABLE);

    softI2C_1::init();

    hal::libs::array<uint8_t, 10> arr;
    for (int i = 0; i < 10; ++i) {
        arr[i] = i;
    }
    memory.write(0, arr);

    _delay_ms(1000);

    while (true) {
        hal::libs::array<uint8_t, 10> arr_r;
        memory.read(0x00, arr_r);

        for (const uint8_t x : arr_r) {
            printf("%d, ", x);
        }
        printf("\r\n");
        _delay_ms(100);
    }
}
