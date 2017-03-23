#include "tests.h"

int main() {
    hal::Serial0.init(9600, hal::STDIO::ENABLE);

    RUN_TESTSUITE(bit_operations);
    RUN_TESTSUITE(compile_time);
    RUN_TESTSUITE(array);
    RUN_TESTSUITE(fifo);
    RUN_TESTSUITE(ReaderTest);
    RUN_TESTSUITE(WriterTest);
    RUN_TESTSUITE(span);
    RUN_TESTSUITE(i2c);
    RUN_TESTSUITE(data_types);
    RUN_TESTSUITE(eeprom);
    RUN_TESTSUITE(terminal);
    RUN_TESTSUITE(AD5641);
    // RUN_TESTSUITE(pure_virtual);
    RUN_TESTSUITE(DigitalIO);

    return 0;
}
