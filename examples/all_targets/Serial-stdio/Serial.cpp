#include <cstdio>
#include "Serial.h"


int main() {
    hal::Serial0.init(9600, hal::STDIO::ENABLE);
    printf("Init!\r\n");

    while (true) {
        std::printf("Write a number:\r\n");
        int x;
        std::scanf("%d", &x);
        std::printf("read: %d\r\n", x);
    }
}
