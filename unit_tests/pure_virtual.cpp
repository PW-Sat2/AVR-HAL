#include "tests.h"

TEST_GROUP(pure_virtual);

struct PureVirtualInterface {
    PureVirtualInterface() {
        auto ptr = this;
        ptr->foo();
    }
    virtual void foo() = 0;
};

struct PureVirtualImplementation : PureVirtualInterface {
    virtual void foo();
};

TEST(pure_virtual, during_construction) {
    PureVirtualImplementation a;
}
