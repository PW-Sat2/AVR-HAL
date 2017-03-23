#include <stdio.h>
#include <avr/interrupt.h>

extern "C" void __cxa_pure_virtual(void);

void __cxa_pure_virtual(void) {
    cli();
    while (1) {
        printf("Virtual invoked!\n");
    }
}
