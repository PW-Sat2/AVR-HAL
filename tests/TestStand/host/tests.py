import unittest, random
from lib import *
from time import sleep


def init_devices():
    avr644 = AVRClient('COM10', 250000)
    avr328 = AVRClient('COM9', 250000)
    # avr128.reset()
    # avr328.reset()
    #s = serial.Serial('COM9', 250000, timeout=10)
    return [avr328, avr644]

@unittest.skip
class GPIOTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.avr128, cls.avr328 = init_devices()

    def test_basic(self):
        a = GPIO(self.avr128, 26, GPIO.Mode.OUTPUT)
        b = GPIO(self.avr328, 27, GPIO.Mode.INPUT)

        for i in xrange(20):
            a.write(1)
            self.assertTrue(a.read())
            self.assertTrue(b.read())

            a.write(0)
            self.assertFalse(a.read())
            self.assertFalse(b.read())

    def write_binary(self, tab, value):
        for i in xrange(len(tab)):
            if value & (1 << i) != 0:
                tab[i].write(1)
            else:
                tab[i].write(0)

    def check_binary(self, tab, value):
        for i in xrange(len(tab)):
            now = tab[i].read()
            if value & (1 << i) != 0:
                self.assertTrue(now)
            else:
                self.assertFalse(now)

    def test_i2c_lines(self):
        i2c_sda = [26, 27]
        i2c_scl = [25, 28]
        i2c_lines_128 = [GPIO(self.avr128, i2c_sda[0], GPIO.Mode.OUTPUT),
                         GPIO(self.avr128, i2c_scl[0], GPIO.Mode.OUTPUT)]

        i2c_lines_328 = [GPIO(self.avr328, i2c_sda[1], GPIO.Mode.INPUT),
                         GPIO(self.avr328, i2c_scl[1], GPIO.Mode.INPUT)]

        for i in xrange(20):
            for i in xrange(4):
                self.write_binary(i2c_lines_128, i)
                self.check_binary(i2c_lines_128, i)
                self.check_binary(i2c_lines_328, i)

        i2c_lines_128 = [GPIO(self.avr128, i2c_sda[0], GPIO.Mode.INPUT),
                         GPIO(self.avr128, i2c_scl[0], GPIO.Mode.INPUT)]

        i2c_lines_328 = [GPIO(self.avr328, i2c_sda[1], GPIO.Mode.OUTPUT),
                         GPIO(self.avr328, i2c_scl[1], GPIO.Mode.OUTPUT)]

        for i in xrange(20):
            for i in xrange(4):
                self.write_binary(i2c_lines_328, i)
                self.check_binary(i2c_lines_328, i)
                self.check_binary(i2c_lines_128, i)

@unittest.skip
class AnalogGPIOTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.avr128, cls.avr328 = init_devices()

    def tearDown(self):
        self.adc.disable()

    def is_around(self, channel, voltage):
        bits = channel.read()
        volt = channel.read_voltage()

        self.assertAlmostEqual(bits*self.reference/1023., volt, delta=0.02)
        self.assertAlmostEqual(voltage, volt, delta=0.5)

    def test_i2c_lines(self):
        self.reference = 5.0
        self.adc = ADC(self.avr328, ADC.Prescaler.DIV_128, ADC.Reference.AVcc, self.reference)
        sda_in = AnalogIO(self.avr328, AnalogIO.Channel.ADC4)
        scl_in = AnalogIO(self.avr328, AnalogIO.Channel.ADC5)

        sda_out = GPIO(self.avr128, 26, GPIO.Mode.OUTPUT)
        scl_out = GPIO(self.avr128, 25, GPIO.Mode.OUTPUT)

        for i in xrange(20):
            sda_out.write(0)
            scl_out.write(0)

            self.is_around(sda_in, 0)
            self.is_around(scl_in, 0)

            sda_out.write(1)
            scl_out.write(0)
            self.is_around(sda_in, 3.3)
            self.is_around(scl_in, 0)

            sda_out.write(0)
            scl_out.write(1)
            self.is_around(sda_in, 0)
            self.is_around(scl_in, 3.3)

            sda_out.write(1)
            scl_out.write(1)
            self.is_around(sda_in, 3.3)
            self.is_around(scl_in, 3.3)



class I2CTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.avr328, cls.avr644 = init_devices()

    def setUp(self):
        self.fails = 0
        self.oks = 1

    def tearDown(self):
        self.printStatus()
        self.i2c_master.disable()
        self.i2c_slave.disable()

    def get_random_tab(self, length, start=0, end=255):
        tab = []
        for i in xrange(length):
            tab.append(int(random.randrange(start, end)))

        return tab

    def printStatus(self):
        print "OKs: ", self.oks, " Fails: ", self.fails
        print "PER = ", float(self.fails)/float(self.oks + self.fails)

    def myAssertEqual(self, a, b):
        # self.assertEqual(a, b)
        if a == b:
            self.oks += 1
        else:
            self.fails += 1
            print "FAIL: ", a, b

    def single_test_write(self):
        tab = self.get_random_tab(random.randrange(1, 9))
        self.i2c_dev.data_transfer(tab, 0)
        self.myAssertEqual(self.i2c_slave.read(), tab)

    def single_test_read_write(self):
        tab_tx = self.get_random_tab(random.randrange(1, 9))
        tab_rx = self.get_random_tab(random.randrange(1, 9))
        self.i2c_slave.buffer_tx_data(tab_rx)
        self.myAssertEqual(self.i2c_dev.data_transfer(tab_tx, len(tab_rx)), tab_rx)
        self.myAssertEqual(self.i2c_slave.read(), tab_tx)

    def single_test_read(self):
        tab = self.get_random_tab(random.randrange(1, 9))
        self.i2c_slave.buffer_tx_data(tab)
        self.myAssertEqual(self.i2c_dev.data_transfer([], len(tab)), tab)

    def single_test(self):
        test_case = random.randrange(0, 3)
        if test_case == 0:
            self.single_test_write()
        elif test_case == 1:
            self.single_test_read()
        elif test_case == 2:
            self.single_test_read_write()

    def test_all_addresses(self):
        addresses = range(1, 128)
        addresses[addresses.index(80)] = 10
        addresses[addresses.index(81)] = 11

        for address in addresses:
            print "addr: ", address
            self.i2c_master = I2CMaster(self.avr328)
            self.i2c_dev = I2CDevice(self.avr328, address)
            self.i2c_slave = I2CSlave(self.avr644, address)

            for i in xrange(2):
                self.single_test_read()
                self.single_test_write()
                self.single_test_read_write()

    def test_comm(self):
        while True:
            address = random.randrange(1, 128)
            if address == 80 or address == 81:
                continue

            print "addr: ", address
            self.i2c_master = I2CMaster(self.avr328)
            self.i2c_dev = I2CDevice(self.avr328, address)
            self.i2c_slave = I2CSlave(self.avr644, address)

            for i in xrange(1000):
                self.single_test()

            self.printStatus()

if __name__ == '__main__':
    unittest.main()
