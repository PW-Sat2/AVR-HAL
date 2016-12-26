#include "Serial.h"

int main() {
    hal::Serial0.init(9600, hal::STDIO::ENABLE);

    while (true) {
        printf("Write value!\r\n");
        int val;
        scanf("%d", &val);
        printf("Read %d\r\n", val);
    }
}
