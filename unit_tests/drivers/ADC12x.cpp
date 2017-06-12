#include <mocks/SPI.h>
#include "mocks/DigitalIO.h"
#include "tests.h"

TEST_GROUP(ADC12x);

using namespace hal;
using namespace hal::libs;
using namespace hal::drivers;

struct ADC12xMock : public EmptySPIMock {
    void transfer(gsl::span<const uint8_t> in, gsl::span<uint8_t> out) override {
        TEST_ASSERT_EQUAL_INT(2, in.size());

        Reader reader_in{in};
        channel = reader_in.ReadByte() >> 3;

        out[0] = value >> 8;
        out[1] = value & 0xFF;
    }

    uint16_t value;
    uint8_t channel;
};

TEST(ADC12x, SetsProperChannel) {
    ADC12xMock mock;
    ADC128 adc128(mock);
    ADC124 adc124(mock);

    adc128.read_and_change_channel(ADC128::Channel::IN0);
    TEST_ASSERT_EQUAL_INT(mock.channel, 0);

    adc128.read_and_change_channel(ADC128::Channel::IN2);
    TEST_ASSERT_EQUAL_INT(mock.channel, 2);

    adc128.read_and_change_channel(ADC128::Channel::IN1);
    TEST_ASSERT_EQUAL_INT(mock.channel, 1);

    adc128.read_and_change_channel(ADC128::Channel::IN7);
    TEST_ASSERT_EQUAL_INT(mock.channel, 7);

    adc128.read_and_change_channel(ADC128::Channel::IN6);
    TEST_ASSERT_EQUAL_INT(mock.channel, 6);

    adc128.read_and_change_channel(ADC128::Channel::IN4);
    TEST_ASSERT_EQUAL_INT(mock.channel, 4);

    adc128.read_and_change_channel(ADC128::Channel::IN3);
    TEST_ASSERT_EQUAL_INT(mock.channel, 3);

    adc128.read_and_change_channel(ADC128::Channel::IN5);
    TEST_ASSERT_EQUAL_INT(mock.channel, 5);

    adc124.read_and_change_channel(ADC124::Channel::IN0);
    TEST_ASSERT_EQUAL_INT(mock.channel, 0);

    adc124.read_and_change_channel(ADC124::Channel::IN2);
    TEST_ASSERT_EQUAL_INT(mock.channel, 2);

    adc124.read_and_change_channel(ADC124::Channel::IN1);
    TEST_ASSERT_EQUAL_INT(mock.channel, 1);

    adc124.read_and_change_channel(ADC124::Channel::IN3);
    TEST_ASSERT_EQUAL_INT(mock.channel, 3);
}

TEST(ADC12x, edgeCases) {
    ADC12xMock mock;
    ADC128 adc128(mock);

    mock.value = 4095;
    TEST_ASSERT_EQUAL_INT(mock.value,
                          adc128.read_and_change_channel(ADC128::Channel::IN0));

    mock.value = 0;
    TEST_ASSERT_EQUAL_INT(mock.value,
                          adc128.read_and_change_channel(ADC128::Channel::IN0));
}

TEST(ADC12x, fullRange) {
    ADC12xMock mock;
    ADC128 adc128(mock);

    for (uint16_t i = 0; i < 4096; ++i) {
        mock.value = i;
        TEST_ASSERT_EQUAL_INT(
            mock.value, adc128.read_and_change_channel(ADC128::Channel::IN0));
    }
}

TEST(ADC12x, OverflowShouldMakeABitMask) {
    ADC12xMock mock;
    ADC128 adc128(mock);

    mock.value = 4096;
    TEST_ASSERT_EQUAL_INT(0, adc128.read_and_change_channel(ADC128::Channel::IN0));

    mock.value = 4097;
    TEST_ASSERT_EQUAL_INT(1, adc128.read_and_change_channel(ADC128::Channel::IN0));

    mock.value = 14785;
    TEST_ASSERT_EQUAL_INT(2497,
                          adc128.read_and_change_channel(ADC128::Channel::IN0));

    mock.value = 65535;
    TEST_ASSERT_EQUAL_INT(4095,
                          adc128.read_and_change_channel(ADC128::Channel::IN0));
}
