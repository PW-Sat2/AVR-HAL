#include <hal/hal>
#include "hal/board.h"

using namespace std::chrono_literals;

int main() {
    while (true) {
        hal::sleep_for(100ms);
    }
}
