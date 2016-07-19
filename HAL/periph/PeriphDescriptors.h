#ifndef HAL_PERIPH_PERIPHDESCRIPTORS_H_
#define HAL_PERIPH_PERIPHDESCRIPTORS_H_

struct DigitalIOPinDescriptor {
    int DDRx, PORTx, PINx;
    uint8_t pin;
};

struct UART_descriptor {
	int UBRRnH, UBRRnL, UCSRnA, UCSRnB, UCSRnC, UDRn;
};


#endif  // HAL_PERIPH_PERIPHDESCRIPTORS_H_
