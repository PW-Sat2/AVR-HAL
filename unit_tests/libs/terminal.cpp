#include <cstdint>
#include <cstdio>

#include "hal/libs/terminal/terminal.h"
#include "tests.h"

TEST_GROUP(terminal);

using namespace hal::libs;

struct CommandTracker {
    bool invoked;
    int argc;
    char** argv;

    void clear() {
        invoked = false;
        argc    = -1;
        argv    = NULL;
    }

    bool wasInvoked() {
        auto tmp = invoked;
        invoked  = false;
        return tmp;
    }

    void invoke(std::uint8_t argc_, char* argv_[]) {
        argc    = argc_;
        argv    = argv_;
        invoked = true;
    }
};

CommandTracker cmds[2];

template<int i>
void handle(std::uint8_t argc, char* argv[]) {
    cmds[i].invoke(argc, argv);
}

TerminalCommandDescription cmdList[] = {"test", handle<0>, "foo", handle<1>};

Terminal terminal;

void prepare() {
    terminal.SetCommandList(cmdList);
    cmds[0].clear();
    cmds[1].clear();
}

void handle(const char* line) {
    static char lineTmp[100];
    strcpy(lineTmp, line);
    terminal.HandleCommand(lineTmp);
}

TEST(terminal, no_arguments) {
    prepare();
    TEST_ASSERT_FALSE(cmds[0].wasInvoked());
    TEST_ASSERT_FALSE(cmds[1].wasInvoked());

    prepare();
    handle("test");
    TEST_ASSERT_TRUE(cmds[0].wasInvoked());
    TEST_ASSERT_FALSE(cmds[1].wasInvoked());

    prepare();
    handle("test ");
    TEST_ASSERT_TRUE(cmds[0].wasInvoked());
    TEST_ASSERT_FALSE(cmds[1].wasInvoked());

    prepare();
    handle("test  ");
    TEST_ASSERT_TRUE(cmds[0].wasInvoked());
    TEST_ASSERT_FALSE(cmds[1].wasInvoked());

    prepare();
    handle("test\t");
    TEST_ASSERT_FALSE(cmds[0].wasInvoked());
    TEST_ASSERT_FALSE(cmds[1].wasInvoked());

    prepare();
    handle(" foo ");
    TEST_ASSERT_FALSE(cmds[0].wasInvoked());
    TEST_ASSERT_TRUE(cmds[1].wasInvoked());
}

TEST(terminal, single_argument) {
    prepare();
    TEST_ASSERT_FALSE(cmds[0].wasInvoked());
    TEST_ASSERT_FALSE(cmds[1].wasInvoked());

    prepare();
    handle("test 1");
    TEST_ASSERT_TRUE(cmds[0].wasInvoked());
    TEST_ASSERT_FALSE(cmds[1].wasInvoked());
    TEST_ASSERT_EQUAL(cmds[0].argc, 1);
    TEST_ASSERT_EQUAL_STRING(cmds[0].argv[0], "1");

    prepare();
    handle("test abc ");
    TEST_ASSERT_TRUE(cmds[0].wasInvoked());
    TEST_ASSERT_FALSE(cmds[1].wasInvoked());
    TEST_ASSERT_EQUAL(cmds[0].argc, 1);
    TEST_ASSERT_EQUAL_STRING(cmds[0].argv[0], "abc");

    prepare();
    handle(" foo           94m1ie]1db        ");
    TEST_ASSERT_FALSE(cmds[0].wasInvoked());
    TEST_ASSERT_TRUE(cmds[1].wasInvoked());
    TEST_ASSERT_EQUAL(cmds[1].argc, 1);
    TEST_ASSERT_EQUAL_STRING(cmds[1].argv[0], "94m1ie]1db");
}

TEST(terminal, more_arguments) {
    prepare();
    TEST_ASSERT_FALSE(cmds[0].wasInvoked());
    TEST_ASSERT_FALSE(cmds[1].wasInvoked());

    prepare();
    handle("test 1 2.0 abc");
    TEST_ASSERT_TRUE(cmds[0].wasInvoked());
    TEST_ASSERT_FALSE(cmds[1].wasInvoked());
    TEST_ASSERT_EQUAL(cmds[0].argc, 3);
    TEST_ASSERT_EQUAL_STRING(cmds[0].argv[0], "1");
    TEST_ASSERT_EQUAL(atoi(cmds[0].argv[0]), 1);
    TEST_ASSERT_EQUAL_STRING(cmds[0].argv[1], "2.0");
    TEST_ASSERT_EQUAL(atof(cmds[0].argv[1]), 2.0);
    TEST_ASSERT_EQUAL_STRING(cmds[0].argv[2], "abc");

    prepare();
    handle("test abc  ");
    TEST_ASSERT_TRUE(cmds[0].wasInvoked());
    TEST_ASSERT_FALSE(cmds[1].wasInvoked());
    TEST_ASSERT_EQUAL(cmds[0].argc, 1);
    TEST_ASSERT_EQUAL_STRING(cmds[0].argv[0], "abc");

    prepare();
    handle("foo          94m1ie]1db        ");
    TEST_ASSERT_FALSE(cmds[0].wasInvoked());
    TEST_ASSERT_TRUE(cmds[1].wasInvoked());
    TEST_ASSERT_EQUAL(cmds[1].argc, 1);
    TEST_ASSERT_EQUAL_STRING(cmds[1].argv[0], "94m1ie]1db");
}
