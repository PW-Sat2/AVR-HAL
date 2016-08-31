import unittest, random
from lib import *
from time import sleep

avr_first = AVRClient('COM9', 250000)
avr_second = AVRClient('COM10', 250000)

avr_first_sda_pin = 27
avr_first_scl_pin = 28

avr_first_miso_pin = 16
avr_first_mosi_pin = 15
avr_first_sck_pin = 17
avr_first_ss_pin = 14

avr_first_sda_adc_channel = ADC.Channel.ADC4
avr_first_scl_adc_channel = ADC.Channel.ADC5

avr_first_analog_reference = 5.0

avr_second_sda_pin = 23
avr_second_scl_pin = 22

avr_second_miso_pin = 7
avr_second_mosi_pin = 6
avr_second_sck_pin = 8
avr_second_ss_pin = 5

disabled_i2c_adresses = [80, 81, 83]


class GPIOTests(unittest.TestCase):
    def test_basic(self):
        a = GPIO(avr_first, avr_first_sda_pin, GPIO.Mode.OUTPUT)
        b = GPIO(avr_second, avr_second_sda_pin, GPIO.Mode.INPUT)

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
    
    def test_spi_lines(self):
        spi_first = [GPIO(avr_first, pin, GPIO.Mode.OUTPUT)
                        for pin in [avr_first_mosi_pin,
                                    avr_first_miso_pin,
                                    avr_first_sck_pin,
                                    avr_first_ss_pin]]
        
        spi_second = [GPIO(avr_second, pin, GPIO.Mode.INPUT)
                        for pin in [avr_second_mosi_pin,
                                    avr_second_miso_pin,
                                    avr_second_sck_pin,
                                    avr_second_ss_pin]]

        for _ in xrange(10):
            for value in xrange(2**4):
                self.write_binary(spi_first, value)
                self.check_binary(spi_first, value)
                self.check_binary(spi_second, value)
            
    def test_i2c_lines(self):
        i2c_first = [GPIO(avr_first, pin, GPIO.Mode.OUTPUT)
                        for pin in [avr_first_sda_pin,
                                    avr_first_scl_pin]]
        
        i2c_second = [GPIO(avr_second, pin, GPIO.Mode.INPUT)
                        for pin in [avr_second_sda_pin,
                                    avr_second_scl_pin]]
        
        for _ in xrange(10):
            for value in xrange(4):
                self.write_binary(i2c_first, value)
                self.check_binary(i2c_second, value)
                self.check_binary(i2c_second, value)

        i2c_first = [GPIO(avr_first, pin, GPIO.Mode.INPUT)
                        for pin in [avr_first_sda_pin,
                                    avr_first_scl_pin]]

        i2c_second = [GPIO(avr_second, pin, GPIO.Mode.OUTPUT)
                        for pin in [avr_second_sda_pin,
                                    avr_second_scl_pin]]

        for _ in xrange(10):
            for value in xrange(4):
                self.write_binary(i2c_second, value)
                self.check_binary(i2c_first, value)
                self.check_binary(i2c_second, value)


class AnalogGPIOTests(unittest.TestCase):
    def tearDown(self):
        self.adc.disable()

    def is_around(self, channel, voltage):
        bits = channel.read()
        volt = channel.read_voltage()

        self.assertAlmostEqual(bits*avr_first_analog_reference/1023., volt, delta=0.02)
        self.assertAlmostEqual(voltage, volt, delta=0.5)

    def test_i2c_lines(self):

        self.adc = ADC(avr_first, ADC.Prescaler.DIV_128, ADC.Reference.AVcc, avr_first_analog_reference)
        sda_in = AnalogIO(avr_first, avr_first_sda_adc_channel)
        scl_in = AnalogIO(avr_first, avr_first_scl_adc_channel)

        sda_out = GPIO(avr_second, avr_second_sda_pin, GPIO.Mode.OUTPUT)
        scl_out = GPIO(avr_second, avr_second_scl_pin, GPIO.Mode.OUTPUT)

        for i in xrange(20):
            sda_out.write(0)
            scl_out.write(0)

            self.is_around(sda_in, 0)
            self.is_around(scl_in, 0)

            sda_out.write(1)
            scl_out.write(0)
            self.is_around(sda_in, 5)
            self.is_around(scl_in, 0)

            sda_out.write(0)
            scl_out.write(1)
            self.is_around(sda_in, 0)
            self.is_around(scl_in, 5)

            sda_out.write(1)
            scl_out.write(1)
            self.is_around(sda_in, 5)
            self.is_around(scl_in, 5)


class I2CTests(unittest.TestCase):
    def setUp(self):
        self.fails = 0
        self.oks = 1
        self.type = 'n'

    def tearDown(self):
        self.i2c_master.disable()
        self.i2c_slave.disable()

    def get_random_tab(self, length, start=0, end=255):
        return [random.randint(start, end) for _ in xrange(length)]

    def printStatus(self):
        print "OKs: ", self.oks, " Fails: ", self.fails
        print "PER = ", float(self.fails)/float(self.oks + self.fails)

    def myAssertEqual(self, a, b):
        self.assertEqual(a, b)
        if a == b:
            self.oks += 1
        else:
            self.fails += 1
            print "FAIL [" + self.type + "]: ", a, b

    def single_test_write(self):
        self.type = 'w'
        tab = self.get_random_tab(random.randint(1, 9))
        self.i2c_dev.data_transfer(tab, 0)
        self.myAssertEqual(self.i2c_slave.read(), tab)

    def single_test_read_write(self):
        self.type = 'rw'
        tab_tx = self.get_random_tab(random.randint(1, 9))
        tab_rx = self.get_random_tab(random.randint(1, 9))
        self.i2c_slave.buffer_tx_data(tab_rx)
        self.myAssertEqual(self.i2c_dev.data_transfer(tab_tx, len(tab_rx)), tab_rx)
        self.myAssertEqual(self.i2c_slave.read(), tab_tx)

    def single_test_read(self):
        self.type = 'r'
        tab = self.get_random_tab(random.randint(1, 9))
        self.i2c_slave.buffer_tx_data(tab)
        self.myAssertEqual(self.i2c_dev.data_transfer([], len(tab)), tab)

    def single_test(self):
        test_case = random.randint(0, 3)
        if test_case == 0:
            self.single_test_write()
        elif test_case == 1:
            self.single_test_read()
        elif test_case == 2:
            self.single_test_read_write()

    def test_all_addresses(self):
        addresses = range(1, 128)

        # disable addresses which are taken by something else
        for i in disabled_i2c_adresses:
            addresses[addresses.index(i)] = 1

        for address in addresses:
            print "addr: ", address
            self.i2c_master = I2CMaster(avr_second)
            self.i2c_dev = I2CDevice(avr_second, address)
            self.i2c_slave = I2CSlave(avr_first, address)

            for i in xrange(10):
                self.single_test_read()
                self.single_test_write()
                self.single_test_read_write()

    def test_comm(self):
        for _ in xrange(1000):
            address = random.randint(1, 128)
            if disabled_i2c_adresses.count(address) > 0:
                continue

            print "addr: ", address
            self.i2c_master = I2CMaster(avr_second)
            self.i2c_dev = I2CDevice(avr_second, address)
            self.i2c_slave = I2CSlave(avr_first, address)

            for i in xrange(10):
                self.single_test()

            self.printStatus()


class SPITests(unittest.TestCase):
    def get_random_tab(self, length, start=0, end=255):
        return [random.randint(start, end) for _ in xrange(length)]

    def test_comm(self):
        spi_master = SPIMaster(avr_first,
                           SPIMaster.Polarity.idle_high,
                           SPIMaster.Phase.leading_sample,
                           SPIMaster.DataOrder.MSB_first,
                           SPIMaster.ClockDivisor.DIV_128)

        spi_device = SPIDevice(avr_first, avr_first_ss_pin)

        spi_slave = SPISlave(avr_second,
                             SPISlave.Polarity.idle_high,
                             SPISlave.Phase.leading_sample,
                             SPISlave.DataOrder.MSB_first)

        for _ in xrange(100):
            slave_data = self.get_random_tab(random.randint(1, 9))
            master_data = self.get_random_tab(len(slave_data))

            spi_slave.buffer_data(slave_data)
            self.assertEqual(spi_device.shift(master_data), slave_data)
            self.assertEqual(spi_slave.read_buffer(), master_data)

if __name__ == '__main__':
    unittest.main()
