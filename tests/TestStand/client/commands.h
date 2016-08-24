#ifndef TESTS_TESTSTAND_CLIENT_COMMANDS_H_
#define TESTS_TESTSTAND_CLIENT_COMMANDS_H_

#include <avr/io.h>
#include <util/delay.h>
#include "DigitalIO.h"
#include "boards.h"
#include "Serial.h"
#include "SPI.h"
#include "SPISlave.h"
#include "Analog.h"
#include "CLI.h"

using namespace hal;

class PingCmd: libs::CLI::Command {
 public:
    PingCmd() : libs::CLI::Command("ping") {
    }
    void callback(const hal::libs::array_view<char *> & parameters)
            override {
        for (auto &&x : parameters) {
            printf("%s ", x);
        }
        printf("\r");
    }
};

class GPIOCmd: libs::CLI::Command {
 public:
    GPIOCmd() :
            libs::CLI::Command("gpio") {
    }
    void callback(const hal::libs::array_view<char *> & parameters)
            override {
        uint8_t pin = atoi(parameters.at(0));
        DigitalIO io { pin, hal::DigitalIO::RUNTIME::ENABLED };

        if (parameters.size() == 1) {
            bool s = io.read();
            printf("%d", s);
        } else {
            switch (parameters.at(1)[0]) {
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

class ADCCmd: libs::CLI::Command {
 public:
    ADCCmd() :
            libs::CLI::Command("an") {
    }
    void callback(const hal::libs::array_view<char *> & parameters)
            override {
        char cmd = parameters.at(0)[0];
        if (cmd == 'i') {
            auto prescaler = static_cast<InternalADC::Prescaler>(atoi(parameters.at(1)));
            auto reference = static_cast<InternalADC::Reference>(atoi(parameters.at(2)));
            float voltage = atof(parameters.at(3));
            InternalADC::init(prescaler, reference, voltage);
        } else if (cmd == 'r') {
            printf("%d\r", InternalADC::read());
        } else if (cmd == 'v') {
            printf("%f\r", InternalADC::read_voltage());
        } else if (cmd == 'd') {
            InternalADC::disable();
        } else if (cmd == 'c') {
            auto ch = static_cast<InternalADC::Input>(atoi(parameters.at(1)));
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

class AnalogIOCmd: libs::CLI::Command {
 public:
    AnalogIOCmd() : libs::CLI::Command("ang") {
    }
    void callback(const hal::libs::array_view<char *> & parameters)
            override {
        auto ch = static_cast<InternalADC::Input>(atoi(parameters.at(1)));
        AnalogGPIO pin{ch};

        char cmd = parameters.at(0)[0];
        if (cmd == 'r') {
            printf("%d\r", pin.read());
        } else if (cmd == 'v') {
            printf("%f\r", pin.read_voltage());
        }
    }
};

class SPIMasterCmd: hal::libs::CLI::Command {
 public:
    SPIMasterCmd() :
            hal::libs::CLI::Command("spi") {
    }
    void callback(const hal::libs::array_view<char *> & parameters)
            override {
        if (parameters.at(0)[0] == 'i') {
            auto polarity   = static_cast<SPI::Polarity>(atoi(parameters.at(1)));
            auto phase      = static_cast<SPI::Phase>(atoi(parameters.at(2)));
            auto data_order = static_cast<SPI::DataOrder>(atoi(parameters.at(3)));
            auto divisor    = static_cast<SPI::ClockDivisor>(atoi(parameters.at(4)));

            SPI::init(polarity, phase, data_order, divisor);
        } else if (parameters.at(0)[0] == 'd') {
            SPI::disable();
        } else {
            for (uint8_t i = 0; i < parameters.size(); ++i) {
                uint8_t now = atoi(parameters.at(i));
                now = SPI::shift(now);
                printf("%d\r", now);
            }
        }
    }
};

class SPIDeviceCmd: hal::libs::CLI::Command {
 public:
    SPIDeviceCmd() :
            hal::libs::CLI::Command("spid") {
    }
    void callback(const hal::libs::array_view<char *> & parameters)
            override {
        auto pin = static_cast<DigitalIO::Pin>(atoi(parameters.at(0)));
        SPI_Device dev{pin, DigitalIO::RUNTIME::ENABLED};
        dev.init();

        libs::array<uint8_t, 10> buf;

        for (uint8_t i = 0; i < parameters.size()-1; ++i) {
            buf[i] = atoi(parameters.at(i+1));
        }
        dev.transfer(libs::make_array_view(buf.data(), parameters.size()-1),
                     libs::make_array_view(buf.data(), parameters.size()-1));
        for (uint8_t i = 0; i < parameters.size()-1; ++i) {
            printf("%d\r", buf[i]);
        }
    }
};

class SPISlaveCmd: hal::libs::CLI::Command {
 public:
    SPISlaveCmd() :
            hal::libs::CLI::Command("spis") {
    }
    void callback(const hal::libs::array_view<char *> & parameters)
            override {
        if (parameters.at(0)[0] == 'i') {
            auto polarity   = static_cast<SPISlave::Polarity>(atoi(parameters.at(1)));
            auto phase      = static_cast<SPISlave::Phase>(atoi(parameters.at(2)));
            auto data_order = static_cast<SPISlave::DataOrder>(atoi(parameters.at(3)));

            SPISlave::init(polarity, phase, data_order);
            SPISlave::enable_interrupt();
        } else if (parameters.at(0)[0] == 'd') {
            SPISlave::disable();
        } else {
            buffer_cnt = 0;
            for (uint8_t i = 0; i < parameters.size(); ++i) {
                buffer[i] = atoi(parameters.at(i));
            }
            SPDR = buffer[0];
            for (uint8_t i = 0; i < parameters.size(); ++i) {
                while (buffer_cnt <= i) {
                }
                printf("%d\r", buffer[i]);
            }
        }
    }

    uint8_t isr(uint8_t received) {
        buffer[buffer_cnt] = received;
        return buffer[++buffer_cnt];
    }

    volatile uint8_t buffer[10];
    volatile uint8_t buffer_cnt = 0;
};

#endif  // TESTS_TESTSTAND_CLIENT_COMMANDS_H_
