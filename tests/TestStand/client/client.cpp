#include <avr/io.h>
#include <util/delay.h>
#include "DigitalIO.h"
#include "boards.h"
#include "Serial.h"
#include "SPISlave.h"
#include "CLI.h"

#include "commands.h"

using namespace hal;

GPIOCmd gpio_cmd;
SPISlaveCmd spislave_cmd;
ADCCmd adc_cmd;
PingCmd ping_cmd;
AnalogIOCmd analogio_cmd;
SPIMasterCmd spimaster_cmd;
SPIDeviceCmd spidevice_cmd;
I2CMasterCmd i2cmaster_cmd;
I2CSlaveCmd i2cslave_cmd;

#if defined(MCU_ATMEGA328P_TQFP32)
constexpr DigitalIO pin1{bsp::pins::D2};
#elif defined(MCU_ATMEGA128A_TQFP64)
constexpr DigitalIO pin1{bsp::pins::PA1};
#elif defined(MCU_ATMEGA644P_DIP40)
constexpr DigitalIO pin1{bsp::pins::A1};
#endif

static char buf[100];
static uint8_t cnt = 0;
static bool cmd_ready_flag = false;

#if defined(MCU_ATMEGA328P_TQFP32)
ISR(USART_RX_vect) {
#elif defined(MCU_ATMEGA128A_TQFP64) || defined(MCU_ATMEGA644P_DIP40)
ISR(USART0_RX_vect) {
#endif
    char now = UDR0;
    buf[cnt++] = now;
    if (now == '\r') {
        buf[cnt-1] = 0;
        pin1.set();
        cmd_ready_flag = true;
        cnt = 0;
    }
}

ISR(SPI_STC_vect) {
    SPDR = spislave_cmd.isr(SPDR);
}

#if defined(MCU_ATMEGA328P_TQFP32) || defined(MCU_ATMEGA644P_DIP40)
constexpr uint32_t baudrate = 250000;
#elif defined(MCU_ATMEGA128A_TQFP64)
constexpr uint32_t baudrate = 230400;
#endif

int main() {
    hal::Serial0.init(baudrate, hal::STDIO::ENABLE);
    hal::Serial0.enable_rx_interrupt();

    pin1.init(DigitalIO::OUTPUT);

    sei();

    uint32_t counter = 0;
    while (true) {
        if (cmd_ready_flag) {
            hal::libs::CLI::parse_line(buf);
            cmd_ready_flag = false;
            pin1.reset();
            Serial0.print_byte(0);
        }
        counter++;
        if (counter == 1000000) {  // ~1 sec delay
            counter = 0;
            Serial0.print_byte(1);
        }
    }
}
