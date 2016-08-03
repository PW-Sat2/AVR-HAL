#include "gtest.h"
#include "I2C.h"
#include "compile_time.h"
#include <vector>

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

std::vector<I2C_Event> events;

class TWI_fake : public I2C_Base {
 public:

    static bool start(uint8_t address, const StartAction_t start_action) {
        events.push_back(I2C_Event(I2C_Event::START, (address << 1) | static_cast<uint8_t>(start_action)));
        return true;
    }

    static void stop(void) {
        events.push_back(I2C_Event(I2C_Event::STOP));
    }

    static bool write(const uint8_t data) {
        events.push_back(I2C_Event(I2C_Event::WRITE, data));
    }

    static uint8_t read(Acknowledge_t ack) {
        if (ack == Acknowledge_t::ACK) {
            events.push_back(I2C_Event(I2C_Event::READ, 1));
        } else {
            events.push_back(I2C_Event(I2C_Event::READ, 0));
        }
    }

    static void write(const libs::array_view<const uint8_t> & arv) {
        auto size = arv.size();
        auto * data = arv.data();
        while (size--) {
            write(*data);
            data++;
        }
    }

    static void read(libs::array_view<uint8_t> arv, Acknowledge_t last_byte_ACK = NACK) {
        auto size = arv.size()-1;
        auto * data = arv.data();
        while(size--) {
            *data = read(ACK);
            data++;
        }
        *data = read(last_byte_ACK);
    }
};

bool operator==(const std::vector<I2C_Event> & lhs,
        const std::vector<I2C_Event> & rhs) {
    if( lhs.size() != rhs.size() )
        return false;
    for(int i = 0; i < lhs.size(); ++i) {
        if( lhs[i] != rhs[i] )
            return false;
    }
    return true;
}

#define PUSH(event) ref.push_back(I2C_Event(I2C_Event:: event))
#define PUSHv(event, val) ref.push_back(I2C_Event(I2C_Event:: event, val))

TEST(i2c, basic) {
    using hal::libs::make_array_view;
    using hal::libs::array_view;
    events.clear();

    TWI_fake::write(0);
    uint8_t data[] = {1, 2, 3};
    TWI_fake::write(make_array_view(data));

    uint8_t data2[4];
    array_view<uint8_t> XXX(data2);
    TWI_fake::read(XXX);
    TWI_fake::read(I2C_Base::ACK);
    TWI_fake::read(I2C_Base::NACK);

    std::vector<I2C_Event> ref;
    ref.push_back(I2C_Event(I2C_Event::WRITE, 0));
    ref.push_back(I2C_Event(I2C_Event::WRITE, 1));
    ref.push_back(I2C_Event(I2C_Event::WRITE, 2));
    ref.push_back(I2C_Event(I2C_Event::WRITE, 3));
    ref.push_back(I2C_Event(I2C_Event::READ, I2C_Base::ACK));
    ref.push_back(I2C_Event(I2C_Event::READ, I2C_Base::ACK));
    ref.push_back(I2C_Event(I2C_Event::READ, I2C_Base::ACK));
    ref.push_back(I2C_Event(I2C_Event::READ, I2C_Base::NACK));
    ref.push_back(I2C_Event(I2C_Event::READ, I2C_Base::ACK));
    ref.push_back(I2C_Event(I2C_Event::READ, I2C_Base::NACK));

    EXPECT_TRUE(ref == events);
}

TEST(i2c, device) {
    using hal::libs::make_array_view;
    using hal::libs::array_view;
    events.clear();
    std::vector<I2C_Event> ref;

#define TEST_AND_CLEAR() \
    EXPECT_TRUE(ref == events); \
    events.clear(); ref.clear();

    constexpr uint8_t addr = 0xF9;
    const uint8_t addr_w = (addr << 1) | static_cast<uint8_t>(I2C_Base::START_WRITE);
    const uint8_t addr_r = (addr << 1) | static_cast<uint8_t>(I2C_Base::START_READ);
    using dev = I2C_Device_t<TWI_fake, addr>;
    dev::write(1);
    PUSHv(START, addr_w);
    PUSHv(WRITE, 1);
    PUSH(STOP);

    TEST_AND_CLEAR();

    uint8_t tab[] = {2, 3};
    dev::write(make_array_view(tab));
    PUSHv(START, addr_w);
    PUSHv(WRITE, 2);
    PUSHv(WRITE, 3);
    PUSH(STOP);
    TEST_AND_CLEAR();

    dev::read(I2C_Base::ACK);
    dev::read(I2C_Base::NACK);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C_Base::Acknowledge_t::ACK);
    PUSH(STOP);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C_Base::Acknowledge_t::NACK);
    PUSH(STOP);
    TEST_AND_CLEAR();

    uint8_t tab2[2];
    array_view<uint8_t> arv(tab2);
    dev::read(arv);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C_Base::Acknowledge_t::ACK);
    PUSHv(READ, I2C_Base::Acknowledge_t::NACK);
    PUSH(STOP);
    TEST_AND_CLEAR();

    dev::read(arv, I2C_Base::Acknowledge_t::NACK);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C_Base::Acknowledge_t::ACK);
    PUSHv(READ, I2C_Base::Acknowledge_t::NACK);
    PUSH(STOP);
    TEST_AND_CLEAR();

    dev::read(arv, I2C_Base::Acknowledge_t::ACK);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C_Base::Acknowledge_t::ACK);
    PUSHv(READ, I2C_Base::Acknowledge_t::ACK);
    PUSH(STOP);
    TEST_AND_CLEAR();

    uint8_t tab_tx[] = {9, 8, 7};
    array_view<uint8_t> arv_tx(tab_tx);
    uint8_t tab_rx[2];
    array_view<uint8_t> arv_rx(tab_rx);
    dev::data_transfer(arv_tx, arv_rx);
    PUSHv(START, addr_w);
    PUSHv(WRITE, 9);
    PUSHv(WRITE, 8);
    PUSHv(WRITE, 7);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C_Base::Acknowledge_t::ACK);
    PUSHv(READ, I2C_Base::Acknowledge_t::NACK);
    PUSH(STOP);
    TEST_AND_CLEAR();

    dev::write_register(0x18, arv_tx);
    PUSHv(START, addr_w);
    PUSHv(WRITE, 0x18);
    PUSHv(WRITE, 9);
    PUSHv(WRITE, 8);
    PUSHv(WRITE, 7);
    PUSH(STOP);
    TEST_AND_CLEAR();

    dev::read_register(0x18, arv_rx);
    PUSHv(START, addr_w);
    PUSHv(WRITE, 0x18);
    PUSHv(START, addr_r);
    PUSHv(READ, I2C_Base::Acknowledge_t::ACK);
    PUSHv(READ, I2C_Base::Acknowledge_t::NACK);
    PUSH(STOP);
    TEST_AND_CLEAR();
}

}  // namespace hal
