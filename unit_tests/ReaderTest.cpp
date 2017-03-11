#include <cstdint>
#include "tests.h"

#include "array.h"
#include "reader.h"

using namespace hal::libs;

TEST(ReaderTest, TestDefaultCtor) {
    Reader reader;
    EXPECT_FALSE(reader.Status());
    EXPECT_EQ(reader.RemainingSize(), 0);
}

TEST(ReaderTest, TestStatusNullBuffer) {
    hal::libs::span<const std::uint8_t> span;
    Reader reader(span);
    EXPECT_FALSE(reader.Status());
}

TEST(ReaderTest, TestStatusZeroSizeBuffer) {
    uint8_t array[1];
    Reader reader;
    reader.Initialize(hal::libs::span<const std::uint8_t>(array, 0));
    EXPECT_FALSE(reader.Status());
}

TEST(ReaderTest, TestCtorStatusValidBuffer) {
    uint8_t array[] = {0x55, 0xaa};

    Reader reader(hal::libs::make_span(array));
    EXPECT_TRUE(reader.Status());
    EXPECT_EQ(reader.RemainingSize(), 2);
}

TEST(ReaderTest, TestStatusValidBuffer) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa};

    reader.Initialize(hal::libs::make_span(array));
    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSingleByte) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa};

    reader.Initialize(hal::libs::make_span(array));
    EXPECT_EQ(reader.ReadByte(), 0x55);
    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestSkip) {
    uint8_t array[] = {0x55, 0xaa};
    Reader reader(hal::libs::make_span(array));
    EXPECT_TRUE(reader.Skip(1));
    EXPECT_TRUE(reader.Status());
    EXPECT_EQ(reader.RemainingSize(), 1);
}

TEST(ReaderTest, TestSkipOverTheLimit) {
    uint8_t array[] = {0x55, 0xaa};
    Reader reader(hal::libs::make_span(array));
    EXPECT_FALSE(reader.Skip(3));
    EXPECT_FALSE(reader.Status());
}

TEST(ReaderTest, TestSkipToTheLimit) {
    uint8_t array[] = {0x55, 0xaa};
    Reader reader(hal::libs::make_span(array));
    EXPECT_TRUE(reader.Skip(2));
    EXPECT_TRUE(reader.Status());
    EXPECT_EQ(reader.RemainingSize(), 0);
}

TEST(ReaderTest, TestReadingSingleByteBeyondEnd) {
    Reader reader;
    uint8_t array[] = {0x55};

    reader.Initialize(hal::libs::make_span(array));
    reader.ReadByte();
    reader.ReadByte();
    EXPECT_FALSE(reader.Status());
}

TEST(ReaderTest, TestReadingWordLE) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa};

    reader.Initialize(hal::libs::make_span(array));
    EXPECT_EQ(reader.ReadWordLE(), 0xaa55);
    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSignedWordLE) {
    uint8_t array[] = {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x7F,
                       0x00, 0x80, 0x68, 0xC5, 0x98, 0x3A};
    Reader reader;
    reader.Initialize(hal::libs::make_span(array));

    EXPECT_EQ(reader.ReadSignedWordLE(), 0);
    EXPECT_EQ(reader.ReadSignedWordLE(), -1);
    EXPECT_EQ(reader.ReadSignedWordLE(), 32767);
    EXPECT_EQ(reader.ReadSignedWordLE(), -32768);
    EXPECT_EQ(reader.ReadSignedWordLE(), -15000);
    EXPECT_EQ(reader.ReadSignedWordLE(), 15000);
    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSignedWordBE) {
    uint8_t array[] = {0x00, 0x00, 0xFF, 0xFF, 0x7F, 0xFF,
                       0x80, 0x00, 0xC5, 0x68, 0x3A, 0x98};
    Reader reader;
    reader.Initialize(hal::libs::make_span(array));

    EXPECT_EQ(reader.ReadSignedWordBE(), 0);
    EXPECT_EQ(reader.ReadSignedWordBE(), -1);
    EXPECT_EQ(reader.ReadSignedWordBE(), 32767);
    EXPECT_EQ(reader.ReadSignedWordBE(), -32768);
    EXPECT_EQ(reader.ReadSignedWordBE(), -15000);
    EXPECT_EQ(reader.ReadSignedWordBE(), 15000);
    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingWordBE) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa};

    reader.Initialize(array);
    EXPECT_EQ(reader.ReadWordBE(), 0x55aa);
    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingWordLEBeyondEnd) {
    Reader reader;
    uint8_t array[] = {0x55};

    reader.Initialize(array);
    reader.ReadWordLE();
    EXPECT_FALSE(reader.Status());
}

TEST(ReaderTest, TestReadingWordBEBeyondEnd) {
    Reader reader;
    uint8_t array[] = {0x55};

    reader.Initialize(array);
    reader.ReadWordBE();
    EXPECT_FALSE(reader.Status());
}

TEST(ReaderTest, TestReadingDWordLE) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77, 0xee};

    reader.Initialize(array);
    EXPECT_EQ(reader.ReadDoubleWordLE(), 0xEE77AA55U);
    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSignedDWordLE) {
    uint8_t array[] = {0x0,  0x0,  0x0,  0x0,  0xFF, 0xFF, 0xFF, 0xFF,
                       0xFF, 0x7F, 0x0,  0x0,  0x0,  0x80, 0xFF, 0xFF,
                       0xFF, 0xFF, 0xFF, 0x7F, 0x0,  0x0,  0x0,  0x80,
                       0xD2, 0x2,  0x96, 0x49, 0x2E, 0xFD, 0x69, 0xB6};
    Reader reader;
    reader.Initialize(array);

    EXPECT_EQ(reader.ReadSignedDoubleWordLE(), 0);
    EXPECT_EQ(reader.ReadSignedDoubleWordLE(), -1);
    EXPECT_EQ(reader.ReadSignedDoubleWordLE(), 32767);
    EXPECT_EQ(reader.ReadSignedDoubleWordLE(), -32768);
    EXPECT_EQ(reader.ReadSignedDoubleWordLE(), 2147483647);
    EXPECT_EQ(reader.ReadSignedDoubleWordLE(), -2147483648);
    EXPECT_EQ(reader.ReadSignedDoubleWordLE(), 1234567890);
    EXPECT_EQ(reader.ReadSignedDoubleWordLE(), -1234567890);

    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSignedDWordBE) {
    uint8_t array[] = {0x0,  0x0,  0x0,  0x0,  0xFF, 0xFF, 0xFF, 0xFF,
                       0x0, 0x0, 0x7F,  0xFF,  0xFF,  0xFF, 0x80, 0x0,
                       0x7F, 0xFF, 0xFF, 0xFF, 0x80,  0x0,  0x0,  0x0,
                       0x49, 0x96,  0x2, 0xD2, 0xB6, 0x69, 0xFD, 0x2E};
    Reader reader;
    reader.Initialize(array);

    EXPECT_EQ(reader.ReadSignedDoubleWordBE(), 0);
    EXPECT_EQ(reader.ReadSignedDoubleWordBE(), -1);
    EXPECT_EQ(reader.ReadSignedDoubleWordBE(), 32767);
    EXPECT_EQ(reader.ReadSignedDoubleWordBE(), -32768);
    EXPECT_EQ(reader.ReadSignedDoubleWordBE(), 2147483647);
    EXPECT_EQ(reader.ReadSignedDoubleWordBE(), -2147483648);
    EXPECT_EQ(reader.ReadSignedDoubleWordBE(), 1234567890);
    EXPECT_EQ(reader.ReadSignedDoubleWordBE(), -1234567890);

    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingDWordBE) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77, 0xee};

    reader.Initialize(array);
    EXPECT_EQ(reader.ReadDoubleWordBE(), 0x55AA77EEU);
    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingQuadWordLE) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77, 0xee, 0x66, 0xcc, 0x44, 0x88};

    reader.Initialize(array);
    EXPECT_EQ(reader.ReadQuadWordLE(), 0x8844CC66EE77AA55ULL);
    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingQuadLEBeyondEnd) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77, 0xee, 0x66, 0xcc, 0x44};

    reader.Initialize(array);
    reader.ReadQuadWordLE();
    EXPECT_FALSE(reader.Status());
}

TEST(ReaderTest, TestReadingDWordLEBeyondEnd) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77};

    reader.Initialize(array);
    reader.ReadDoubleWordLE();
    EXPECT_FALSE(reader.Status());
}

TEST(ReaderTest, TestReadArray) {
    Reader reader;
    const uint8_t array[] = {0x55, 0xaa, 0x77};

    reader.Initialize(array);
    EXPECT_TRUE(reader.ReadArray(3) == hal::libs::make_span(array));
    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadArrayBeyondEnd) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77};

    reader.Initialize(array);
    EXPECT_TRUE(reader.ReadArray(4).empty());
    EXPECT_FALSE(reader.Status());
}

TEST(ReaderTest, TestReadingMovesPosition) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77, 0xee, 0x11, 0x22, 0x33,
                       0x44, 0x55, 0x66, 0x77, 0x88, 0x99};

    reader.Initialize(array);
    EXPECT_EQ(reader.ReadByte(), 0x55);
    EXPECT_EQ(reader.ReadWordLE(), 0x77AA);
    EXPECT_EQ(reader.ReadDoubleWordLE(), 0x332211EEU);
    EXPECT_TRUE(reader.ReadArray(3) ==
                hal::libs::span<const std::uint8_t>(array + 7, 3));
    EXPECT_EQ(reader.ReadByte(), 0x77);
    EXPECT_EQ(reader.ReadWordBE(), 0x8899);
    EXPECT_TRUE(reader.Status());
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
    EXPECT_FALSE(reader.Status());
}

TEST(ReaderTest, TestRemainigSizeNoDataRead) {
    Reader reader;
    uint8_t array[] = {0x55};

    reader.Initialize(array);
    EXPECT_EQ(reader.RemainingSize(), 1);
}

TEST(ReaderTest, TestRemainigSize) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77, 0xee, 0x11, 0x22,
                       0x33, 0x44, 0x55, 0x66, 0x77};

    reader.Initialize(array);
    reader.ReadByte();
    reader.ReadWordLE();
    reader.ReadDoubleWordLE();
    EXPECT_EQ(reader.RemainingSize(), static_cast<int32_t>(sizeof(array) - 7));
}

TEST(ReaderTest, TestRemainigSizeAtTheEnd) {
    Reader reader;
    uint8_t array[] = {0x55, 0xaa, 0x77, 0xee, 0x11, 0x22, 0x33,
                       0x44, 0x55, 0x66, 0x77, 0x88, 0x99};

    reader.Initialize(array);
    reader.ReadByte();
    reader.ReadWordLE();
    reader.ReadDoubleWordLE();
    reader.ReadArray(3);
    reader.ReadByte();
    reader.ReadWordBE();
    EXPECT_EQ(reader.RemainingSize(), 0);
}

TEST(ReaderTest, TestReadingToEnd) {
    hal::libs::array<uint8_t, 5> a{1, 2, 3, 4, 5};

    Reader reader(a);

    reader.ReadByte();

    auto toEnd = reader.ReadToEnd();
    EXPECT_EQ(2, toEnd[0]);
    EXPECT_EQ(3, toEnd[1]);
    EXPECT_EQ(4, toEnd[2]);
    EXPECT_EQ(5, toEnd[3]);
}

TEST(ReaderTest, TestReadingToEndWhenNothingLeftIsCorrect) {
    hal::libs::array<uint8_t, 1> a{1};

    Reader reader(a);

    reader.ReadByte();

    EXPECT_EQ(reader.ReadToEnd().size(), 0);
    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSingleBCDByte) {
    Reader reader;
    uint8_t array[] = {0x11, 0xaa};

    reader.Initialize(array);
    EXPECT_EQ(reader.ReadByteBCD(0xf0), 11);
    EXPECT_TRUE(reader.Status());
}

TEST(ReaderTest, TestReadingSingleBCDByteWithPartialNibbleMask) {
    Reader reader;
    uint8_t array[] = {0b10100010, 0xaa};

    reader.Initialize(array);
    EXPECT_EQ(reader.ReadByteBCD(0b00110000), 22);
    EXPECT_TRUE(reader.Status());
}

DEFINE_TESTSUITE(ReaderTest);
