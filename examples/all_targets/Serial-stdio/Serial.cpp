#include <cstdio>
#include <hal/hal>

using hal::Serial0;

int main() {
    Serial0.init(115200);
    Serial0.redirect_stdio();
    Serial0.redirect_stderr();
    printf("Init!\r\n");

    while (true) {
        std::printf("Write a number:\r\n");
        int x;
        std::scanf("%d", &x);
        std::printf("read: %d\r\n", x);
    }
}
