#include <hal/hal>
#include "tests.h"

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release(__guard *);
extern "C" void __cxa_guard_abort(__guard *);
int __cxa_guard_acquire(__guard *g) {return !*reinterpret_cast<char *>(g);}
void __cxa_guard_release(__guard *g) {*reinterpret_cast<char *>(g) = 1;}
void __cxa_guard_abort(__guard *) {}

typedef void (*fptr)();

fptr add_test_group(void (*fun)(), bool get) {
    static hal::libs::FIFO_data<void (*)(), 100> test_groups;

    if (get) {
        return test_groups.get();
    } else {
        test_groups.append(fun);
        return nullptr;
    }
}

int main() {
    hal::Serial0.init(9600, hal::STDIO::ENABLE);

    while (true) {
        auto fun = add_test_group(nullptr, true);
        if (fun == nullptr) {
            break;
        }
        fun();
    }
}
