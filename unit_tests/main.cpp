#include "Serial.h"
#include "tests.h"

INC_TESTSUITE(bit_operations);
INC_TESTSUITE(compile_time);
INC_TESTSUITE(array);
INC_TESTSUITE(fifo);
INC_TESTSUITE(ReaderTest);
INC_TESTSUITE(WriterTest);
INC_TESTSUITE(span);
INC_TESTSUITE(i2c);
INC_TESTSUITE(data_types);

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

    return 0;
}