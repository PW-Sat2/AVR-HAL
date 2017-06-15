#include "tests.h"

TEST_GROUP(SPI);

using namespace hal;

using pin_ss   = DigitalIO::GPIO<mcu::pin_ss>;
using pin_sck  = DigitalIO::GPIO<mcu::pin_sck>;
using pin_mosi = DigitalIO::GPIO<mcu::pin_mosi>;
using pin_miso = DigitalIO::GPIO<mcu::pin_miso>;

TEST(SPI, SckIdleState) {
    {
        using spi = SPI::Hardware<pin_ss,
                                  SPI::HardwareClockDivisor::SPIHard_DIV_128,
                                  SPI::Polarity::idle_high,
                                  SPI::Phase::leading_sample,
                                  SPI::DataOrder::LSB_first>;
        spi::init();
        spi::transfer(0xFF);

        TEST_ASSERT_EQUAL_UINT8(true, pin_sck::read());

        spi::disable();
    }
    {
        using spi = SPI::Hardware<pin_ss,
                                  SPI::HardwareClockDivisor::SPIHard_DIV_128,
                                  SPI::Polarity::idle_low,
                                  SPI::Phase::leading_sample,
                                  SPI::DataOrder::LSB_first>;
        spi::init();
        spi::transfer(0xFF);

        TEST_ASSERT_EQUAL_UINT8(false, pin_sck::read());

        spi::disable();
    }
    {
        using spi = SPI::Software<pin_mosi,                 //
                                  pin_miso,                 //
                                  pin_sck,                  //
                                  pin_ss,                   //
                                  SPI::Polarity::idle_low,  //
                                  SPI::Phase::leading_sample>;
        spi::init();
        spi::transfer(0xFF);

        TEST_ASSERT_EQUAL_UINT8(false, pin_sck::read());

        spi::disable();
    }
    {
        using spi = SPI::Software<pin_mosi,                  //
                                  pin_miso,                  //
                                  pin_sck,                   //
                                  pin_ss,                    //
                                  SPI::Polarity::idle_high,  //
                                  SPI::Phase::leading_sample>;
        spi::init();
        spi::transfer(0xFF);

        TEST_ASSERT_EQUAL_UINT8(true, pin_sck::read());

        spi::disable();
    }
}

TEST(SPI, transfer) {
    {
        using spi = SPI::Hardware<pin_ss,
                                  SPI::HardwareClockDivisor::SPIHard_DIV_128,
                                  SPI::Polarity::idle_high,
                                  SPI::Phase::leading_sample,
                                  SPI::DataOrder::LSB_first>;
        spi::init();
        for (int i = 0; i <= 0xFF; ++i) {
            TEST_ASSERT_EQUAL_UINT8(spi::transfer(i), i);
        }
        spi::disable();
    }

    {
        using spi = SPI::Software<pin_mosi,                  //
                                  pin_miso,                  //
                                  pin_sck,                   //
                                  pin_ss,                    //
                                  SPI::Polarity::idle_high,  //
                                  SPI::Phase::leading_sample>;
        spi::init();
        for (int i = 0; i <= 0xFF; ++i) {
            TEST_ASSERT_EQUAL_UINT8(spi::transfer(i), i);
        }
        spi::disable();
    }
}
