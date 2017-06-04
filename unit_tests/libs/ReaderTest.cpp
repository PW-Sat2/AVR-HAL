#include <cstdint>
#include "tests.h"

using namespace hal::libs;

TEST_GROUP(ReaderTest);

TEST(ReaderTest, TestDefaultCtor) {
    Reader reader;
    TEST_ASSERT_FALSE(reader.Status());
    TEST_ASSERT_EQUAL(reader.RemainingSize(), 0);
}

TEST(ReaderTest, TestStatusNullBuffer) {
    hal::libs::span<const std::uint8_t> span;
    Reader reader(span);
    TEST_ASSERT_FALSE(reader.Status());
}

TEST(ReaderTest, TestStatusZeroSizeBuffer) {
    uint8_t array[1];
    Reader reader;
    reader.Initialize(hal::libs::span<const std::uint8_t>(array, 0));
    TEST_ASSERT_FALSE(reader.Status());
}

TEST(ReaderTest, TestCtorStatusValidBuffer) {
    uint8_t array[] = {0x55, 0xaa};

    Reader reader(hal::libs::make_span(array));
    TEST_ASSERT_TRUE(reader.Status());
    TEST_ASSERT_EQUAL(reader.RemainingSize(), 2);
}

TEST(ReaderTest, TestStatusValidBuffer) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa};

    reader.Initialize(hal::libs::make_span(array));
    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSingleByte) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa};

    reader.Initialize(hal::libs::make_span(array));
    TEST_ASSERT_EQUAL(reader.ReadByte(), 0x55);
    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestSkip) {
    uint8_t array[] = {0x55, 0xaa};
    Reader reader(hal::libs::make_span(array));
    TEST_ASSERT_TRUE(reader.Skip(1));
    TEST_ASSERT_TRUE(reader.Status());
    TEST_ASSERT_EQUAL(reader.RemainingSize(), 1);
}

TEST(ReaderTest, TestSkipOverTheLimit) {
    uint8_t array[] = {0x55, 0xaa};
    Reader reader(hal::libs::make_span(array));
    TEST_ASSERT_FALSE(reader.Skip(3));
    TEST_ASSERT_FALSE(reader.Status());
}

TEST(ReaderTest, TestSkipToTheLimit) {
    uint8_t array[] = {0x55, 0xaa};
    Reader reader(hal::libs::make_span(array));
    TEST_ASSERT_TRUE(reader.Skip(2));
    TEST_ASSERT_TRUE(reader.Status());
    TEST_ASSERT_EQUAL(reader.RemainingSize(), 0);
}

TEST(ReaderTest, TestReadingSingleByteBeyondEnd) {
    Reader reader;
    uint8_t array[] = {0x55};

    reader.Initialize(hal::libs::make_span(array));
    reader.ReadByte();
    reader.ReadByte();
    TEST_ASSERT_FALSE(reader.Status());
}

TEST(ReaderTest, TestReadingWordLE) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa};

    reader.Initialize(hal::libs::make_span(array));
    TEST_ASSERT_EQUAL(reader.ReadWordLE(), 0xaa55);
    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSignedWordLE) {
    uint8_t array[] = {
        0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x80, 0x68, 0xC5, 0x98, 0x3A};
    Reader reader;
    reader.Initialize(hal::libs::make_span(array));

    TEST_ASSERT_EQUAL(reader.ReadSignedWordLE(), 0);
    TEST_ASSERT_EQUAL(reader.ReadSignedWordLE(), -1);
    TEST_ASSERT_EQUAL(reader.ReadSignedWordLE(), 32767);
    TEST_ASSERT_EQUAL(reader.ReadSignedWordLE(), -32768);
    TEST_ASSERT_EQUAL(reader.ReadSignedWordLE(), -15000);
    TEST_ASSERT_EQUAL(reader.ReadSignedWordLE(), 15000);
    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSignedWordBE) {
    uint8_t array[] = {
        0x00, 0x00, 0xFF, 0xFF, 0x7F, 0xFF, 0x80, 0x00, 0xC5, 0x68, 0x3A, 0x98};
    Reader reader;
    reader.Initialize(hal::libs::make_span(array));

    TEST_ASSERT_EQUAL(reader.ReadSignedWordBE(), 0);
    TEST_ASSERT_EQUAL(reader.ReadSignedWordBE(), -1);
    TEST_ASSERT_EQUAL(reader.ReadSignedWordBE(), 32767);
    TEST_ASSERT_EQUAL(reader.ReadSignedWordBE(), -32768);
    TEST_ASSERT_EQUAL(reader.ReadSignedWordBE(), -15000);
    TEST_ASSERT_EQUAL(reader.ReadSignedWordBE(), 15000);
    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingWordBE) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa};

    reader.Initialize(array);
    TEST_ASSERT_EQUAL(reader.ReadWordBE(), 0x55aa);
    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingWordLEBeyondEnd) {
    Reader reader;
    uint8_t array[] = {0x55};

    reader.Initialize(array);
    reader.ReadWordLE();
    TEST_ASSERT_FALSE(reader.Status());
}

TEST(ReaderTest, TestReadingWordBEBeyondEnd) {
    Reader reader;
    uint8_t array[] = {0x55};

    reader.Initialize(array);
    reader.ReadWordBE();
    TEST_ASSERT_FALSE(reader.Status());
}

TEST(ReaderTest, TestReadingDWordLE) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77, 0xee};

    reader.Initialize(array);
    TEST_ASSERT_EQUAL(reader.ReadDoubleWordLE(), 0xEE77AA55U);
    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSignedDWordLE) {
    uint8_t array[] = {0x0,  0x0,  0x0,  0x0,  0xFF, 0xFF, 0xFF, 0xFF,
                       0xFF, 0x7F, 0x0,  0x0,  0x0,  0x80, 0xFF, 0xFF,
                       0xFF, 0xFF, 0xFF, 0x7F, 0x0,  0x0,  0x0,  0x80,
                       0xD2, 0x2,  0x96, 0x49, 0x2E, 0xFD, 0x69, 0xB6};
    Reader reader;
    reader.Initialize(array);

    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordLE(), 0);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordLE(), -1);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordLE(), 32767);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordLE(), -32768);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordLE(), 2147483647);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordLE(), -2147483648);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordLE(), 1234567890);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordLE(), -1234567890);

    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSignedDWordBE) {
    uint8_t array[] = {0x0,  0x0,  0x0,  0x0,  0xFF, 0xFF, 0xFF, 0xFF,
                       0x0,  0x0,  0x7F, 0xFF, 0xFF, 0xFF, 0x80, 0x0,
                       0x7F, 0xFF, 0xFF, 0xFF, 0x80, 0x0,  0x0,  0x0,
                       0x49, 0x96, 0x2,  0xD2, 0xB6, 0x69, 0xFD, 0x2E};
    Reader reader;
    reader.Initialize(array);

    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordBE(), 0);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordBE(), -1);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordBE(), 32767);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordBE(), -32768);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordBE(), 2147483647);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordBE(), -2147483648);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordBE(), 1234567890);
    TEST_ASSERT_EQUAL(reader.ReadSignedDoubleWordBE(), -1234567890);

    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingDWordBE) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77, 0xee};

    reader.Initialize(array);
    TEST_ASSERT_EQUAL(reader.ReadDoubleWordBE(), 0x55AA77EEU);
    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingQuadWordLE) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77, 0xee, 0x66, 0xcc, 0x44, 0x88};

    reader.Initialize(array);
    TEST_ASSERT_EQUAL(reader.ReadQuadWordLE(), 0x8844CC66EE77AA55ULL);
    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingQuadLEBeyondEnd) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77, 0xee, 0x66, 0xcc, 0x44};

    reader.Initialize(array);
    reader.ReadQuadWordLE();
    TEST_ASSERT_FALSE(reader.Status());
}

TEST(ReaderTest, TestReadingDWordLEBeyondEnd) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77};

    reader.Initialize(array);
    reader.ReadDoubleWordLE();
    TEST_ASSERT_FALSE(reader.Status());
}

TEST(ReaderTest, TestReadArray) {
    Reader reader;
    const uint8_t array[] = {0x55, 0xaa, 0x77};

    reader.Initialize(array);
    TEST_ASSERT_TRUE(reader.ReadArray(3) == hal::libs::make_span(array));
    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadArrayBeyondEnd) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77};

    reader.Initialize(array);
    TEST_ASSERT_TRUE(reader.ReadArray(4).empty());
    TEST_ASSERT_FALSE(reader.Status());
}

TEST(ReaderTest, TestReadingMovesPosition) {
    Reader reader;
    uint8_t array[] = {
        0x55, 0xaa, 0x77, 0xee, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};

    reader.Initialize(array);
    TEST_ASSERT_EQUAL(reader.ReadByte(), 0x55);
    TEST_ASSERT_EQUAL(reader.ReadWordLE(), 0x77AA);
    TEST_ASSERT_EQUAL(reader.ReadDoubleWordLE(), 0x332211EEU);
    TEST_ASSERT_TRUE(reader.ReadArray(3) ==
                     hal::libs::span<const std::uint8_t>(array + 7, 3));
    TEST_ASSERT_EQUAL(reader.ReadByte(), 0x77);
    TEST_ASSERT_EQUAL(reader.ReadWordBE(), 0x8899);
    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingWithInvalidState) {
    Reader reader;
    uint8_t array[] = {0x55};

    reader.Initialize(array);
    reader.ReadByte();
    reader.ReadWordLE();
    reader.ReadWordBE();
    reader.ReadDoubleWordLE();
    reader.ReadArray(3);
    reader.ReadByte();
    TEST_ASSERT_FALSE(reader.Status());
}

TEST(ReaderTest, TestRemainigSizeNoDataRead) {
    Reader reader;
    uint8_t array[] = {0x55};

    reader.Initialize(array);
    TEST_ASSERT_EQUAL(reader.RemainingSize(), 1);
}

TEST(ReaderTest, TestRemainigSize) {
    Reader reader;
    uint8_t array[] = {
        0x55, 0xaa, 0x77, 0xee, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};

    reader.Initialize(array);
    reader.ReadByte();
    reader.ReadWordLE();
    reader.ReadDoubleWordLE();
    TEST_ASSERT_EQUAL(reader.RemainingSize(),
                      static_cast<int32_t>(sizeof(array) - 7));
}

TEST(ReaderTest, TestRemainigSizeAtTheEnd) {
    Reader reader;
    uint8_t array[] = {
        0x55, 0xaa, 0x77, 0xee, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};

    reader.Initialize(array);
    reader.ReadByte();
    reader.ReadWordLE();
    reader.ReadDoubleWordLE();
    reader.ReadArray(3);
    reader.ReadByte();
    reader.ReadWordBE();
    TEST_ASSERT_EQUAL(reader.RemainingSize(), 0);
}

TEST(ReaderTest, TestReadingToEnd) {
    std::array<uint8_t, 5> a{1, 2, 3, 4, 5};

    Reader reader(a);

    reader.ReadByte();

    auto toEnd = reader.ReadToEnd();
    TEST_ASSERT_EQUAL(2, toEnd[0]);
    TEST_ASSERT_EQUAL(3, toEnd[1]);
    TEST_ASSERT_EQUAL(4, toEnd[2]);
    TEST_ASSERT_EQUAL(5, toEnd[3]);
}

TEST(ReaderTest, TestReadingToEndWhenNothingLeftIsCorrect) {
    std::array<uint8_t, 1> a{1};

    Reader reader(a);

    reader.ReadByte();

    TEST_ASSERT_EQUAL(reader.ReadToEnd().size(), 0);
    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSingleBCDByte) {
    Reader reader;
    uint8_t array[] = {0x11, 0xaa};

    reader.Initialize(array);
    TEST_ASSERT_EQUAL(reader.ReadByteBCD(0xf0), 11);
    TEST_ASSERT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSingleBCDByteWithPartialNibbleMask) {
    Reader reader;
    uint8_t array[] = {0b10100010, 0xaa};

    reader.Initialize(array);
    TEST_ASSERT_EQUAL(reader.ReadByteBCD(0b00110000), 22);
    TEST_ASSERT_TRUE(reader.Status());
}
