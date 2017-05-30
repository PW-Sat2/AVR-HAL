#include <hal/hal>

#include "tests.h"

using namespace hal;

TEST_GROUP(SPIHardware);

DigitalIO::GPIO<mcu::pin_ss> gpio;
DigitalIO::Interface& gpioif = gpio;

TEST(SPIHardware, init) {
    {
        SPI::Hardware<SPI::HardwareClockDivisor::SPIHard_DIV_4,
                      SPI::Polarity::idle_low,
                      SPI::Phase::leading_sample,
                      SPI::DataOrder::MSB_first>
            spi(gpio);

        SPCR = 0;
        spi.init();

        uint8_t expected = (1 << SPE) |   //
                           (1 << MSTR) |  //
                           (0) |          //
                           (0 << CPHA) |  //
                           (0 << CPOL) |  //
                           (0 << DORD);

        TEST_ASSERT_EQUAL(expected, SPCR);
    }
    {
        SPI::Hardware<SPI::HardwareClockDivisor::SPIHard_DIV_64,
                      SPI::Polarity::idle_high,
                      SPI::Phase::leading_sample,
                      SPI::DataOrder::MSB_first>
            spi(gpio);

        SPCR = 0;
        spi.init();

        uint8_t expected = (1 << SPE) |   //
                           (1 << MSTR) |  //
                           (2) |          //
                           (0 << CPHA) |  //
                           (1 << CPOL) |  //
                           (0 << DORD);

        TEST_ASSERT_EQUAL(expected, SPCR);
    }
    {
        SPI::Hardware<SPI::HardwareClockDivisor::SPIHard_DIV_16,
                      SPI::Polarity::idle_low,
                      SPI::Phase::trailing_sample,
                      SPI::DataOrder::MSB_first>
            spi(gpio);

        SPCR = 0;
        spi.init();

        uint8_t expected = (1 << SPE) |   //
                           (1 << MSTR) |  //
                           (1) |          //
                           (1 << CPHA) |  //
                           (0 << CPOL) |  //
                           (0 << DORD);

        TEST_ASSERT_EQUAL(expected, SPCR);
    }
    {
        SPI::Hardware<SPI::HardwareClockDivisor::SPIHard_DIV_128,
                      SPI::Polarity::idle_high,
                      SPI::Phase::leading_sample,
                      SPI::DataOrder::LSB_first>
            spi(gpio);

        SPCR = 0;
        spi.init();

        uint8_t expected = (1 << SPE) |   //
                           (1 << MSTR) |  //
                           (3) |          //
                           (0 << CPHA) |  //
                           (1 << CPOL) |  //
                           (1 << DORD);

        TEST_ASSERT_EQUAL(expected, SPCR);
    }
}

TEST(SPIHardware, transferCompletes) {
    SPI::Hardware<SPI::HardwareClockDivisor::SPIHard_DIV_128,
                  SPI::Polarity::idle_high,
                  SPI::Phase::leading_sample,
                  SPI::DataOrder::LSB_first>
        spi(gpio);

    spi.init();
    spi.transfer(0xAA);
}

TEST(SPIHardware, disable) {
    SPI::Hardware<SPI::HardwareClockDivisor::SPIHard_DIV_128,
                  SPI::Polarity::idle_high,
                  SPI::Phase::leading_sample,
                  SPI::DataOrder::LSB_first>
        spi(gpio);

    spi.init();
    TEST_ASSERT_NOT_EQUAL(0, SPCR);
    spi.disable();
    TEST_ASSERT_EQUAL(0, SPCR);
}
