#include <algorithm>
#include "tests.h"

using namespace hal::libs;

TEST_GROUP(WriterTest);


void CheckBuffer(const uint8_t* current, const uint16_t currentLength,
                 const uint8_t* expected, const uint16_t expectedLength) {
    auto in = hal::libs::make_span(current, currentLength);
    auto out = hal::libs::make_span(expected, expectedLength);
    TEST_ASSERT_TRUE(std::equal(in.begin(), in.end(), out.begin()));
}

TEST(WriterTest, TestStatusNullBuffer) {
    Writer writer;
    TEST_ASSERT_FALSE(writer.Status());
}

TEST(WriterTest, TestStatusZeroSizeBuffer) {
    uint8_t array[1];
    Writer writer(hal::libs::make_span(array, 0));
    TEST_ASSERT_FALSE(writer.Status());
}

TEST(WriterTest, TestStatusValidBuffer) {
    uint8_t array[5];
    Writer writer(array);
    TEST_ASSERT_TRUE(writer.Status());
}

TEST(WriterTest, TestBytesWrittenOnStart) {
    uint8_t array[1];
    Writer writer(array);
    TEST_ASSERT_EQUAL(writer.GetDataLength(), 0);
}

TEST(WriterTest, TestWritingSingleByte) {
    uint8_t array[1];
    const uint8_t expected[1] = {0x55};
    Writer writer(array);
    TEST_ASSERT_TRUE(writer.WriteByte(0x55));
    TEST_ASSERT_TRUE(writer.Status());
    CheckBuffer(array, writer.GetDataLength(), expected, sizeof(expected));
}

TEST(WriterTest, TestWritingSingleWordLE) {
    uint8_t array[2];
    const uint8_t expected[2] = {0xAA, 0x55};
    Writer writer(array);
    TEST_ASSERT_TRUE(writer.WriteWordLE(0x55aa));
    TEST_ASSERT_TRUE(writer.Status());
    CheckBuffer(array, writer.GetDataLength(), expected, sizeof(expected));
}

TEST(WriterTest, TestWritingSignedSingleWordLE) {
    uint8_t array[12];
    Writer writer(array);

    const uint8_t expected[] = {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x7F,
                                0x00, 0x80, 0x68, 0xC5, 0x98, 0x3A};

    TEST_ASSERT_TRUE(writer.WriteSignedWordLE(0));
    TEST_ASSERT_TRUE(writer.WriteSignedWordLE(-1));
    TEST_ASSERT_TRUE(writer.WriteSignedWordLE(32767));
    TEST_ASSERT_TRUE(writer.WriteSignedWordLE(-32768));
    TEST_ASSERT_TRUE(writer.WriteSignedWordLE(-15000));
    TEST_ASSERT_TRUE(writer.WriteSignedWordLE(15000));

    TEST_ASSERT_TRUE(writer.Status());
    CheckBuffer(array, writer.GetDataLength(), expected, sizeof(expected));
}

TEST(WriterTest, TestWritingSingleDoubleWordLE) {
    uint8_t array[4];
    const uint8_t expected[4] = {0xEE, 0x77, 0xAA, 0x55};
    Writer writer(array);
    TEST_ASSERT_TRUE(writer.WriteDoubleWordLE(0x55aa77ee));
    TEST_ASSERT_TRUE(writer.Status());
    CheckBuffer(array, writer.GetDataLength(), expected, sizeof(expected));
}

TEST(WriterTest, TestWritingSignedDoubleWordLE) {
    uint8_t array[32];
    const uint8_t expected[32] = {
        0x0, 0x0,  0x0,  0x0,  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x0,
        0x0, 0x0,  0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x0,  0x0,
        0x0, 0x80, 0xD2, 0x2,  0x96, 0x49, 0x2E, 0xFD, 0x69, 0xB6};
    Writer writer(array);
    TEST_ASSERT_TRUE(writer.WriteSignedDoubleWordLE(0));
    TEST_ASSERT_TRUE(writer.WriteSignedDoubleWordLE(-1));
    TEST_ASSERT_TRUE(writer.WriteSignedDoubleWordLE(32767));
    TEST_ASSERT_TRUE(writer.WriteSignedDoubleWordLE(-32768));
    TEST_ASSERT_TRUE(writer.WriteSignedDoubleWordLE(2147483647));
    TEST_ASSERT_TRUE(writer.WriteSignedDoubleWordLE(-2147483648));
    TEST_ASSERT_TRUE(writer.WriteSignedDoubleWordLE(1234567890));
    TEST_ASSERT_TRUE(writer.WriteSignedDoubleWordLE(-1234567890));
    TEST_ASSERT_TRUE(writer.Status());
    CheckBuffer(array, writer.GetDataLength(), expected, sizeof(expected));
}

TEST(WriterTest, TestWritingSingleQuadWordLE) {
    uint8_t array[8];
    const uint8_t expected[8] = {0xEE, 0x77, 0xAA, 0x55,
                                 0xCC, 0x66, 0x88, 0x44};
    Writer writer(array);
    TEST_ASSERT_TRUE(writer.WriteQuadWordLE(0x448866CC55aa77eeull));
    TEST_ASSERT_TRUE(writer.Status());
    CheckBuffer(array, writer.GetDataLength(), expected, sizeof(expected));
}

TEST(WriterTest, TestWritingArray) {
    uint8_t input[] = {0x11, 0x22, 0x33};
    uint8_t array[4];
    const uint8_t expected[] = {0x11, 0x22, 0x33};
    Writer writer(array);
    TEST_ASSERT_TRUE(writer.WriteArray(input));
    TEST_ASSERT_TRUE(writer.Status());
    CheckBuffer(array, writer.GetDataLength(), expected, sizeof(expected));
}

TEST(WriterTest, TestWritingSingleByteBeyondEnd) {
    uint8_t array[1];
    Writer writer(array);
    writer.WriteByte(0x55);
    TEST_ASSERT_FALSE(writer.WriteByte(0x55));
    TEST_ASSERT_FALSE(writer.Status());
}

TEST(WriterTest, TestWritingSingleWordLEBeyondEnd) {
    uint8_t array[1];
    Writer writer(array);
    TEST_ASSERT_FALSE(writer.WriteWordLE(0x55aa));
    TEST_ASSERT_FALSE(writer.Status());
}

TEST(WriterTest, TestWritingSingleDoubleWordLEBeyondEnd) {
    uint8_t array[3];
    Writer writer(array);
    TEST_ASSERT_FALSE(writer.WriteDoubleWordLE(0x55aa77ee));
    TEST_ASSERT_FALSE(writer.Status());
}

TEST(WriterTest, TestWritingSingleQuadWordLEBeyondEnd) {
    uint8_t array[7];
    Writer writer(array);
    TEST_ASSERT_FALSE(writer.WriteQuadWordLE(0x448866CC55aa77eeull));
    TEST_ASSERT_FALSE(writer.Status());
}

TEST(WriterTest, TestWritingArrayBeyondEnd) {
    uint8_t input[] = {0x11, 0x22, 0x33};
    uint8_t array[2];
    Writer writer(array);
    TEST_ASSERT_FALSE(writer.WriteArray(input));
    TEST_ASSERT_FALSE(writer.Status());
}

TEST(WriterTest, TestPositionIsAdvanced) {
    uint8_t input[] = {0x11, 0x22, 0x33};
    uint8_t array[12];
    const uint8_t expected[] = {0x55, 0xAA, 0x55, 0xEE, 0x77,
                                0xAA, 0x55, 0x11, 0x22, 0x33};
    Writer writer(array);
    writer.WriteByte(0x55);
    writer.WriteWordLE(0x55aa);
    writer.WriteDoubleWordLE(0x55aa77ee);
    writer.WriteArray(input);
    CheckBuffer(array, writer.GetDataLength(), expected, sizeof(expected));
}

TEST(WriterTest, TestBytesWritten) {
    uint8_t array[12];
    Writer writer(array);
    writer.WriteByte(0x55);
    writer.WriteWordLE(0x55aa);
    writer.WriteDoubleWordLE(0x55aa77ee);
    TEST_ASSERT_EQUAL(writer.GetDataLength(), 7);
}

TEST(WriterTest, TestUsedSpan) {
    uint8_t array[12];
    Writer writer(array);
    writer.WriteByte(0x55);
    writer.WriteByte(0x66);

    auto s = writer.Capture();

    TEST_ASSERT_EQUAL(s.length(), 2);
    // TEST_ASSERT_TRUE(s == hal::libs::make_span({0x55, 0x66}));
}

TEST(WriterTest, TestWriteLowerBytesBE) {
    uint32_t num = 0xAABBCCDD;

    uint8_t array[3];
    Writer writer(array);

    writer.WriteLowerBytesBE(num, 3);

    TEST_ASSERT_EQUAL(array[0], 0xBB);
    TEST_ASSERT_EQUAL(array[1], 0xCC);
    TEST_ASSERT_EQUAL(array[2], 0xDD);
}

TEST(WriterTest, TestReserveBuffer) {
    uint8_t array[5];
    Writer writer(array);

    writer.WriteByte(1);
    auto b = writer.Reserve(3);
    b[0] = 2;
    b[1] = 3;
    b[2] = 4;
    writer.WriteByte(5);

    // TEST_ASSERT_TRUE(array == {1, 2, 3, 4, 5});
}

TEST(WriterTest, TestReserveBufferOverflowingBuffer) {
    uint8_t array[3];
    Writer writer(array);

    auto b = writer.Reserve(5);

    TEST_ASSERT_EQUAL(b.size(), 3);
    TEST_ASSERT_TRUE(writer.Status());

    writer.WriteByte(1);

    TEST_ASSERT_FALSE(writer.Status());
}
