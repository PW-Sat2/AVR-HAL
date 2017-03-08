#include <stdio.h>
__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release(__guard *);
extern "C" void __cxa_guard_abort(__guard *);
extern "C" void __cxa_pure_virtual(void);

int __cxa_guard_acquire(__guard *g) {
    return !*reinterpret_cast<char *>(g);
}

void __cxa_guard_release(__guard *g) {
    *reinterpret_cast<char *>(g) = 1;
}

void __cxa_guard_abort(__guard *) {
}

void __cxa_pure_virtual(void) {
    while (1) {
        printf("Virtual invoked!\n");
    }
}
