#ifndef TESTS_TESTSTAND_CLIENT_COMMANDS_H_
#define TESTS_TESTSTAND_CLIENT_COMMANDS_H_

#include <avr/io.h>
#include <util/delay.h>
#include "Analog.h"
#include "DigitalIO.h"
#include "SPI.h"
#include "SPISlave.h"
#include "Serial.h"
#include "TWI.h"
#include "TWISlave.h"
#include "Watchdog.h"

#include "CLI.h"

using namespace hal;

class PingCmd : libs::CLI::Command {
 public:
    PingCmd() : libs::CLI::Command("ping") {
    }
    void callback(const hal::libs::span<char*>& parameters) override {
        for (auto&& x : parameters) {
            printf("%s ", x);
        }
        printf("\r");
    }
};

class ResetCmd : libs::CLI::Command {
 public:
    ResetCmd() : libs::CLI::Command("reset") {
    }
    void callback(const hal::libs::span<char*>& parameters) override {
        hal::Watchdog::enable(mcu::Watchdog::Period::p_2000ms);
    }
};

class GPIOCmd : libs::CLI::Command {
 public:
    GPIOCmd() : libs::CLI::Command("gpio") {
    }
    void callback(const hal::libs::span<char*>& parameters) override {
        uint8_t pin = atoi(parameters[0]);
        DigitalIO io{pin, hal::DigitalIO::RUNTIME::ENABLED};

        if (parameters.size() == 1) {
            bool s = io.read();
            printf("%d\r", s);
        } else {
            switch (parameters[1][0]) {
                case '1':
                    io.set();
                    break;
                case '0':
                    io.reset();
                    break;
                case 'o':
                    io.init(DigitalIO::OUTPUT);
                    break;
                case 'i':
                    io.init(DigitalIO::INPUT);
                    break;
                case 'p':
                    io.init(DigitalIO::INPUT_PULLUP);
                    break;
            }
        }
    }
};

volatile int ADC_reading;

ISR(ADC_vect) {
    ADC_reading = InternalADC::read_nowait();
}

class ADCCmd : libs::CLI::Command {
 public:
    ADCCmd() : libs::CLI::Command("an") {
    }
    void callback(const hal::libs::span<char*>& parameters) override {
        char cmd = parameters[0][0];
        if (cmd == 'i') {
            auto prescaler =
                static_cast<InternalADC::Prescaler>(atoi(parameters[1]));
            auto reference =
                static_cast<InternalADC::Reference>(atoi(parameters[2]));
            float voltage = atof(parameters[3]);
            InternalADC::init(prescaler, reference, voltage);
        } else if (cmd == 'r') {
            printf("%d\r", InternalADC::read());
        } else if (cmd == 'v') {
            printf("%f\r", InternalADC::read_voltage());
        } else if (cmd == 'd') {
            InternalADC::disable();
        } else if (cmd == 'c') {
            auto ch = static_cast<InternalADC::Input>(atoi(parameters[1]));
            InternalADC::select_channel(ch);
        } else if (cmd == 'n') {
            //            InternalADC::enable_interrupt();
            //            sei();
            //            hal::cpu::set_sleep_mode(hal::cpu::SleepModes::ADC_Noise_Reduction);
            //            hal::cpu::sleep_enable();
            //            hal::cpu::sleep_cpu();  // triggers ADC conversion
            //
            //            printf("%d\r", ADC_reading);
            //
            //            hal::cpu::sleep_disable();
            //            InternalADC::disable_interrupt();
        }
    }
};

class AnalogIOCmd : libs::CLI::Command {
 public:
    AnalogIOCmd() : libs::CLI::Command("ang") {
    }
    void callback(const hal::libs::span<char*>& parameters) override {
        auto ch = static_cast<InternalADC::Input>(atoi(parameters[1]));
        AnalogGPIO pin{ch};

        char cmd = parameters[0][0];
        if (cmd == 'r') {
            printf("%d\r", pin.read());
        } else if (cmd == 'v') {
            printf("%f\r", pin.read_voltage());
        }
    }
};

class SPIMasterCmd : hal::libs::CLI::Command {
 public:
    SPIMasterCmd() : hal::libs::CLI::Command("spi") {
    }
    void callback(const hal::libs::span<char*>& parameters) override {
        if (parameters[0][0] == 'i') {
            auto polarity   = static_cast<SPI::Polarity>(atoi(parameters[1]));
            auto phase      = static_cast<SPI::Phase>(atoi(parameters[2]));
            auto data_order = static_cast<SPI::DataOrder>(atoi(parameters[3]));
            auto divisor = static_cast<SPI::ClockDivisor>(atoi(parameters[4]));

            SPI::init(polarity, phase, data_order, divisor);
        } else if (parameters[0][0] == 'd') {
            SPI::disable();
        } else {
            for (uint8_t i = 0; i < parameters.size(); ++i) {
                uint8_t now = atoi(parameters[i]);
                now         = SPI::shift(now);
                printf("%d ", now);
            }
            printf("\r");
        }
    }
};

class SPIDeviceCmd : hal::libs::CLI::Command {
 public:
    SPIDeviceCmd() : hal::libs::CLI::Command("spid") {
    }
    void callback(const hal::libs::span<char*>& parameters) override {
        auto pin = static_cast<DigitalIO::Pin>(atoi(parameters[0]));
        SPI_Device dev{pin, DigitalIO::RUNTIME::ENABLED};
        dev.init();

        libs::array<uint8_t, 10> buf;

        for (uint8_t i = 0; i < parameters.size() - 1; ++i) {
            buf[i] = atoi(parameters[i + 1]);
        }
        dev.transfer(libs::make_span(buf.data(), parameters.size() - 1),
                     libs::make_span(buf.data(), parameters.size() - 1));
        for (uint8_t i = 0; i < parameters.size() - 1; ++i) {
            printf("%d ", buf[i]);
        }
        printf("\r");
    }
};


class SPISlaveCmd : hal::libs::CLI::Command {
 public:
    SPISlaveCmd() : hal::libs::CLI::Command("ss") {
    }
    void callback(const hal::libs::span<char*>& parameters) override {
        if (parameters[0][0] == 'i') {
            auto polarity = static_cast<SPISlave::Polarity>(atoi(parameters[1]));
            auto phase    = static_cast<SPISlave::Phase>(atoi(parameters[2]));
            auto data_order =
                static_cast<SPISlave::DataOrder>(atoi(parameters[3]));

            SPISlave::init(polarity, phase, data_order);
            SPISlave::enable_interrupt();
        } else if (parameters[0][0] == 'd') {
            SPISlave::disable();
        } else if (parameters[0][0] == 'r') {
            for (uint8_t i = 0; i < buffer_cnt; ++i) {
                printf("%d ", buffer[i]);
            }
            printf("\r");
        } else {
            buffer_cnt = 0;
            for (uint8_t i = 0; i < parameters.size(); ++i) {
                buffer[i] = atoi(parameters[i]);
            }
            SPDR = buffer[0];
        }
    }

    uint8_t isr(uint8_t received) {
        buffer[buffer_cnt] = received;
        return buffer[++buffer_cnt];
    }

    volatile uint8_t buffer[10];
    volatile uint8_t buffer_cnt = 0;
};


class I2CMasterCmd : hal::libs::CLI::Command {
 public:
    I2CMasterCmd() : hal::libs::CLI::Command("im") {
    }
    void callback(const hal::libs::span<char*>& parameters) override {
        if (parameters[0][0] == 'i') {
            TWI::disable();
            TWI::init<100000>();
        } else if (parameters[0][0] == 'd') {
            TWI::disable();
        } else {
            uint8_t addr           = atoi(parameters[0]);
            uint8_t bytes_to_write = parameters.size() - 2;
            uint8_t bytes_to_read  = atoi(parameters[1 + bytes_to_write]);

            hal::libs::array<uint8_t, 10> tx_buf, rx_buf;

            for (uint8_t i = 0; i < bytes_to_write; ++i) {
                tx_buf[i] = atoi(parameters[1 + i]);
            }

            auto tx_data = hal::libs::span<uint8_t>{tx_buf.data(), bytes_to_write};
            auto rx_data = hal::libs::span<uint8_t>{rx_buf.data(), bytes_to_read};

            I2C_Device<TWI> device{addr};
            if (bytes_to_read == 0) {
                device.write(tx_data);
            } else if (bytes_to_write == 0) {
                device.read(rx_data);
            } else {
                device.data_transfer(tx_data, rx_data);
            }

            for (uint8_t i = 0; i < bytes_to_read; ++i) {
                printf("%d ", rx_buf[i]);
            }
            printf("\r");
        }
    }
};

volatile bool twi_was_callbacked = false;

void TWISlave::callback() {
    twi_was_callbacked = true;
}

class I2CSlaveCmd : hal::libs::CLI::Command {
 public:
    I2CSlaveCmd() : hal::libs::CLI::Command("is") {
    }
    void callback(const hal::libs::span<char*>& parameters) override {
        if (parameters[0][0] == 'i') {
            uint8_t address = atoi(parameters[1]);
            TWISlave::disable();
            TWISlave::init(address);
        } else if (parameters[0][0] == 'd') {
            TWISlave::disable();
        } else if (parameters[0][0] == 'r') {
            if (twi_was_callbacked) {
                for (uint8_t i = 0; i < TWISlave::rx_buffer_cnt; ++i) {
                    printf("%d ", TWISlave::rx_buffer[i]);
                }
            } else {
                for (uint8_t i = 0; i < TWISlave::rx_buffer_cnt; ++i) {
                    printf("0 ");
                }
            }
            printf("\r");
            twi_was_callbacked = false;
        } else {
            for (uint8_t i = 0; i < parameters.size(); ++i) {
                TWISlave::tx_buffer[i] = atoi(parameters[i]);
            }
        }
    }
};

#endif  // TESTS_TESTSTAND_CLIENT_COMMANDS_H_
