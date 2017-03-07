#include "tests.h"

#include "I2C.h"
#include "compile_time.h"

#include "fifo.h"

namespace hal {

class I2C_Event {
 public:
    enum Type {
        START,
        STOP,
        READ,
        WRITE
    };
    Type type;
    uint8_t payload;

    I2C_Event() {}
    I2C_Event(Type type, uint8_t payload = 0) :
        type(type), payload(payload) {
    }

    bool operator==(const I2C_Event & rhs) const {
        if (type != rhs.type || payload != rhs.payload) {
            return false;
        }
        return true;
    }

    bool operator!=(const I2C_Event & rhs) const {
        return (!(*this == rhs));
    }
};

constexpr int FIFOS_N = 100;

hal::libs::FIFO_data<I2C_Event, FIFOS_N> events;

class TWI_fake : public I2C {
 public:
    static bool start(uint8_t address, const StartAction start_action) {
        events.append(I2C_Event(I2C_Event::START, (address << 1) | static_cast<uint8_t>(start_action)));
        return true;
    }

    static void stop(void) {
        events.append(I2C_Event(I2C_Event::STOP));
    }

    static bool write(const uint8_t data) {
        events.append(I2C_Event(I2C_Event::WRITE, data));
        return true;
    }

    static uint8_t read(Acknowledge ack) {
        if (ack == ACK) {
            events.append(I2C_Event(I2C_Event::READ, 1));
        } else {
            events.append(I2C_Event(I2C_Event::READ, 0));
        }
        return true;
    }

    static void write(const libs::span<const uint8_t> & arv) {
        auto size = arv.size();
        auto * data = arv.data();
        while (size--) {
            write(*data);
            data++;
        }
    }

    static void read(libs::span<uint8_t> arv, Acknowledge last_byte_ACK = NACK) {
        auto size = arv.size()-1;
        auto * data = arv.data();
        while (size--) {
            *data = read(ACK);
            data++;
        }
        *data = read(last_byte_ACK);
    }
};

bool operator==(const hal::libs::FIFO_data<I2C_Event, FIFOS_N>& lhs,
                const hal::libs::FIFO_data<I2C_Event, FIFOS_N>& rhs) {

    const I2C_Event * left_ptr;
    auto left_size = lhs.getContinousPart(left_ptr);

    const I2C_Event * right_ptr;
    auto right_size = rhs.getContinousPart(right_ptr);


    auto left = hal::libs::make_span(left_ptr, left_size);
    auto right = hal::libs::make_span(right_ptr, right_size);
    
    return std::equal(left.begin(), left.end(), right.begin());
}

#define PUSH(event) ref.append(I2C_Event(I2C_Event:: event))
#define PUSHv(event, val) ref.append(I2C_Event(I2C_Event:: event, val))
#define TEST_AND_CLEAR() \
    EXPECT_TRUE(ref == events); \
    events.flush(); ref.flush();

TEST(i2c, basic) {
    using hal::libs::make_span;
    using hal::libs::span;
    events.flush();

    TWI_fake::write(0);
    uint8_t data[] = {1, 2, 3};
    TWI_fake::write(make_span(data));

    uint8_t data2[4];
    span<uint8_t> XXX(data2);
    TWI_fake::read(XXX);
    TWI_fake::read(I2C::ACK);
    TWI_fake::read(I2C::NACK);

    hal::libs::FIFO_data<I2C_Event, FIFOS_N> ref;
    ref.append(I2C_Event(I2C_Event::WRITE, 0));
    ref.append(I2C_Event(I2C_Event::WRITE, 1));
    ref.append(I2C_Event(I2C_Event::WRITE, 2));
    ref.append(I2C_Event(I2C_Event::WRITE, 3));
    ref.append(I2C_Event(I2C_Event::READ, I2C::ACK));
    ref.append(I2C_Event(I2C_Event::READ, I2C::ACK));
    ref.append(I2C_Event(I2C_Event::READ, I2C::ACK));
    ref.append(I2C_Event(I2C_Event::READ, I2C::NACK));
    ref.append(I2C_Event(I2C_Event::READ, I2C::ACK));
    ref.append(I2C_Event(I2C_Event::READ, I2C::NACK));

    TEST_AND_CLEAR();
}

TEST(i2c, device) {
    using hal::libs::make_span;
    using hal::libs::span;
    events.flush();
    hal::libs::FIFO_data<I2C_Event, FIFOS_N> ref;



    constexpr uint8_t addr = 0x09;
    const uint8_t addr_w = (addr << 1) | static_cast<uint8_t>(I2C::StartAction::write);
    const uint8_t addr_r = (addr << 1) | static_cast<uint8_t>(I2C::StartAction::read);
    hal::I2C_Device<TWI_fake> dev(addr);
    dev.write(1);
    PUSHv(START, addr_w);
    PUSHv(WRITE, 1);
    PUSH(STOP);

    TEST_AND_CLEAR();

    uint8_t tab[] = {2, 3};
    dev.write(make_span(tab));
    PUSHv(START, addr_w);
    PUSHv(WRITE, 2);
    PUSHv(WRITE, 3);
    PUSH(STOP);
    TEST_AND_CLEAR();

    dev.read(I2C::ACK);
    dev.read(I2C::NACK);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C::Acknowledge::ACK);
    PUSH(STOP);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C::Acknowledge::NACK);
    PUSH(STOP);
    TEST_AND_CLEAR();

    uint8_t tab2[2];
    span<uint8_t> arv(tab2);
    dev.read(arv);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C::Acknowledge::ACK);
    PUSHv(READ, I2C::Acknowledge::NACK);
    PUSH(STOP);
    TEST_AND_CLEAR();

    dev.read(arv, I2C::Acknowledge::NACK);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C::Acknowledge::ACK);
    PUSHv(READ, I2C::Acknowledge::NACK);
    PUSH(STOP);
    TEST_AND_CLEAR();

    dev.read(arv, I2C::Acknowledge::ACK);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C::Acknowledge::ACK);
    PUSHv(READ, I2C::Acknowledge::ACK);
    PUSH(STOP);
    TEST_AND_CLEAR();

    uint8_t tab_tx[] = {9, 8, 7};
    span<uint8_t> arv_tx(tab_tx);
    uint8_t tab_rx[2];
    span<uint8_t> arv_rx(tab_rx);
    dev.data_transfer(arv_tx, arv_rx);
    PUSHv(START, addr_w);
    PUSHv(WRITE, 9);
    PUSHv(WRITE, 8);
    PUSHv(WRITE, 7);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C::Acknowledge::ACK);
    PUSHv(READ, I2C::Acknowledge::NACK);
    PUSH(STOP);
    TEST_AND_CLEAR();

    dev.write_register(0x18, arv_tx);
    PUSHv(START, addr_w);
    PUSHv(WRITE, 0x18);
    PUSHv(WRITE, 9);
    PUSHv(WRITE, 8);
    PUSHv(WRITE, 7);
    PUSH(STOP);
    TEST_AND_CLEAR();

    dev.read_register(0x18, arv_rx);
    PUSHv(START, addr_w);
    PUSHv(WRITE, 0x18);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C::Acknowledge::ACK);
    PUSHv(READ, I2C::Acknowledge::NACK);
    PUSH(STOP);
    TEST_AND_CLEAR();
}

}  // namespace hal

DEFINE_TESTSUITE(i2c);