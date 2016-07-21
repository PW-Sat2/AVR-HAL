#include <stdio.h>
#include "Serial.h"


int main() {
    hal::Serial0.init(9600, hal::STDIO::ENABLE);
    printf("Init!\r\n");

    while (true) {
        printf("Write a number:\r\n");
        int x;
        scanf("%d", &x);
        printf("read: %d\r\n", x);
    }
}
