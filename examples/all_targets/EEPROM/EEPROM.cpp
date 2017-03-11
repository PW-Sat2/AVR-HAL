#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "Serial.h"
#include "eeprom.h"

using namespace hal;


static EepromStorage<int> eepromVariable;

int main() {
    Serial0.init(9600, hal::STDIO::ENABLE);

    while (1) {
        printf("Choose: r - read, w - write: ");
        char c;
        scanf("%c", &c);
        printf("\n");

        if (c == 'r') {
            int readed = eepromVariable;
            printf("Read: %d\n", readed);
        }
        if (c == 'w') {
            int val;
            scanf("%d", &val);
            eepromVariable = val;
        }
    }
}
