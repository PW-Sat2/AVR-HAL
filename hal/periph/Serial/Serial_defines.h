// coding: utf-8
/* Copyright (c) 2011, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef HAL_PERIPH_SERIAL_SERIAL_DEFINES_H_
#define HAL_PERIPH_SERIAL_SERIAL_DEFINES_H_

// Atmel made a mess with the register names for UART0 between the "old"
// devices. To avoid to much conditional compiling we try to mimic the new names
// for the old devices.

#if defined(UDR) and not defined(UDR0)
#define UDR0 UDR
#endif
#if defined(UBRRL) and not defined(UBRR0L)
#define UBRR0L UBRRL
#endif
#if defined(UBRRH) and not defined(UBRR0H)
#define UBRR0H UBRRH
#endif
#if defined(UCSRA) and not defined(UCSR0A)
#define UCSR0A UCSRA
#endif
#if defined(UCSRB) and not defined(UCSR0B)
#define UCSR0B UCSRB
#endif
#if defined(UCSRC) and not defined(UCSR0C)
#define UCSR0C UCSRC
#endif
#if defined(DOR) and not defined(DOR0)
#define DOR0 DOR
#endif
#if defined(FE) and not defined(FE0)
#define FE0 FE
#endif
#if defined(RXCIE) and not defined(RXCIE0)
#define RXCIE0 RXCIE
#endif
#if defined(TXCIE) and not defined(TXCIE0)
#define TXCIE0 TXCIE
#endif
#if defined(RXEN) and not defined(RXEN0)
#define RXEN0 RXEN
#endif
#if defined(TXEN) and not defined(TXEN0)
#define TXEN0 TXEN
#endif
#if defined(U2X) and not defined(U2X0)
#define U2X0 U2X
#endif
#if defined(URSEL) and not defined(URSEL0)
#define URSEL0 URSEL
#endif
#if defined(UCSZ0) and not defined(UCSZ00)
#define UCSZ00 UCSZ0
#endif
#if defined(UCSZ1) and not defined(UCSZ01)
#define UCSZ01 UCSZ1
#endif
#if defined(UDRIE) and not defined(UDRIE0)
#define UDRIE0 UDRIE
#endif

// We want the interrupt names to be "USART0_RX_vect", "USART0_UDRE_vect" and
// "USART0_TX_vect".
#if defined(USART_RX_vect) and not defined(USART0_RX_vect)
#define USART0_RX_vect USART_RX_vect
#endif
#if defined(USART_UDRE_vect) and not defined(USART0_UDRE_vect)
#define USART0_UDRE_vect USART_UDRE_vect
#endif
#if defined(USART_TX_vect) and not defined(USART0_TX_vect)
#define USART0_TX_vect USART_TX_vect
#endif

// ATMega162 is crazy about USART0/1 RX and TX which have an extra 'C' for
// 'complete'
#if defined(USART0_RXC_vect) and not defined(USART0_RX_vect)
#define USART0_RX_vect USART0_RXC_vect
#endif
#if defined(USART1_RXC_vect) and not defined(USART1_RX_vect)
#define USART1_RX_vect USART1_RXC_vect
#endif
#if defined(USART0_TXC_vect) and not defined(USART0_TX_vect)
#define USART0_TX_vect USART0_TXC_vect
#endif
#if defined(USART1_TXC_vect) and not defined(USART1_TX_vect)
#define USART1_TX_vect USART1_TXC_vect
#endif

#if defined(USARTRXC_vect) and not defined(USART0_RX_vect)
#define USART0_RX_vect USARTRXC_vect
#endif
#if defined(USARTUDRE_vect) and not defined(USART0_UDRE_vect)
#define USART0_UDRE_vect USARTUDRE_vect
#endif
#if defined(USARTTXC_vect) and not defined(USART0_TX_vect)
#define USART0_TX_vect USARTTXC_vect
#endif

#if defined(USART_RXC_vect) and not defined(USART0_RX_vect)
#define USART0_RX_vect USART_RXC_vect
#endif
#if defined(USART_UDRE_vect) and not defined(USART0_UDRE_vect)
#define USART0_UDRE_vect USART_UDRE_vect
#endif
#if defined(USART_TXC_vect) and not defined(USART0_TX_vect)
#define USART0_TX_vect USART_TXC_vect
#endif

#endif  // HAL_PERIPH_SERIAL_SERIAL_DEFINES_H_
