#include "tests.h"

TEST_GROUP(SPI);

using namespace hal;

DigitalIO::GPIO<mcu::pin_ss> pin_ss;
DigitalIO::GPIO<mcu::pin_sck> pin_sck;
DigitalIO::GPIO<mcu::pin_mosi> pin_mosi;
DigitalIO::GPIO<mcu::pin_miso> pin_miso;

TEST(SPI, SckIdleState) {
    {
        SPI::Hardware<SPI::HardwareClockDivisor::SPIHard_DIV_128,
                      SPI::Polarity::idle_high,
                      SPI::Phase::leading_sample,
                      SPI::DataOrder::LSB_first>
            spi(pin_ss);
        spi.init();
        spi.transfer(0xFF);

        TEST_ASSERT_EQUAL_UINT8(true, pin_sck.read());

        spi.disable();
    }
    {
        SPI::Hardware<SPI::HardwareClockDivisor::SPIHard_DIV_128,
                      SPI::Polarity::idle_low,
                      SPI::Phase::leading_sample,
                      SPI::DataOrder::LSB_first>
            spi(pin_ss);
        spi.init();
        spi.transfer(0xFF);

        TEST_ASSERT_EQUAL_UINT8(false, pin_sck.read());

        spi.disable();
    }
    {
        SPI::Software<SPI::Polarity::idle_low,  //
                      SPI::Phase::leading_sample>
            spi(pin_mosi, pin_miso, pin_sck, pin_ss);
        spi.init();
        spi.transfer(0xFF);

        TEST_ASSERT_EQUAL_UINT8(false, pin_sck.read());

        spi.disable();
    }
    {
        SPI::Software<SPI::Polarity::idle_high,  //
                      SPI::Phase::leading_sample>
            spi(pin_mosi, pin_miso, pin_sck, pin_ss);
        spi.init();
        spi.transfer(0xFF);

        TEST_ASSERT_EQUAL_UINT8(true, pin_sck.read());

        spi.disable();
    }
}

TEST(SPI, transfer) {
    {
        SPI::Hardware<SPI::HardwareClockDivisor::SPIHard_DIV_128,
                      SPI::Polarity::idle_high,
                      SPI::Phase::leading_sample,
                      SPI::DataOrder::LSB_first>
            spi(pin_ss);
        spi.init();
        for (int i = 0; i <= 0xFF; ++i) {
            TEST_ASSERT_EQUAL_UINT8(spi.transfer(i), i);
        }
        spi.disable();
    }

    {
        SPI::Software<SPI::Polarity::idle_high,  //
                      SPI::Phase::leading_sample>
            spis(pin_mosi, pin_miso, pin_sck, pin_ss);
        spis.init();
        for (int i = 0; i <= 0xFF; ++i) {
            TEST_ASSERT_EQUAL_UINT8(spis.transfer(i), i);
        }
        spis.disable();
    }
}
