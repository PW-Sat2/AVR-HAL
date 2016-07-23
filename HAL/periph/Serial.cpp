#include "Serial.h"

namespace hal {

template<int serial_num>
char Serial<serial_num>::buffer[] = { 0 };

template<int serial_num>
void (*Serial<serial_num>::rx_handler)(uint8_t) = nullptr;


#if SERIALs > 0
ISR(USART0_RX_vect) {
    Serial<0>::rx_handler(UDR0);
}
#endif

#if SERIALs > 1
ISR(USART1_RX_vect) {
    Serial<1>::rx_handler(UDR1);
}
#endif

#if SERIALs > 2
ISR(USART2_RX_vect) {
    Serial<2>::rx_handler(UDR2);
}
#endif

#if SERIALs > 3
ISR(USART3_RX_vect) {
    Serial<3>::rx_handler(UDR3);
}
#endif

}  // namespace hal
