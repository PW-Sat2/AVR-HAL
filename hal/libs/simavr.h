#ifndef HAL_LIBS_SIMAVR_H_
#define HAL_LIBS_SIMAVR_H_

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <cstdlib>

namespace hal {
namespace libs {
namespace sim {

/*!
 * This method will stop simulation in simavr.
 * Run it to finish simulation.
 */
[[noreturn]] inline static void stop_simulation() {
    // when processor goes to sleep with interrupts disabled
    // simavr will stop the simulation
    cli();
    sleep_mode();

    // processor will be halted already
    // this line is to satisfy compiler about [[noreturn]]
    abort();
}

}  // namespace sim
}  // namespace libs
}  // namespace hal

#endif  // HAL_LIBS_SIMAVR_H_
