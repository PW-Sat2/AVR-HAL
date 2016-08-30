import serial, sys, io, threading
from time import sleep, time

DEBUG = False


class AVRClient:
    def __init__(self, com, speed=115200):
        self.serial = serial.Serial(com, speed, timeout=1)
        self.ser_io = io.TextIOWrapper(io.BufferedRWPair(self.serial, self.serial, 1),
                                       newline='\r',
                                       line_buffering=True)
        self.wait_for_device()
        print "Connected!"
        self.flush()
        self.send("ping 1 2 3")
        print self.read()
        self.cmd_fin()

    def send(self, cmd):
        if DEBUG:
            print "sending: ", cmd
        self.serial.write(cmd + '\r')

    def send_command(self, cmd):
        self.send(cmd)
        self.cmd_fin()

    def send_command_and_read_line(self, cmd):
        self.send(cmd)
        line = self.read()
        self.cmd_fin()
        return line

    def read(self):
        s = self.ser_io.readline().replace('\x00','').replace('\x01','')
        if DEBUG:
            print "readed: ", s
        return s

    def flush(self):
        self.serial.flushInput()
        self.serial.flushOutput()
        while self.serial.inWaiting() > 0:
            self.serial.read()

    def wait_for_null(self):
        start = time()
        while self.serial.read(1) != '\0':
            now = time()
            if now-start > 1:
                raise RuntimeError('Timeout waiting for end of command')

    def wait_for_device(self):
        start = time()
        while self.serial.read(1) != '\1':
            now = time()
            if now-start > 30:
                raise RuntimeError('Timeout waiting for device')

    def cmd_fin(self):
        self.wait_for_null()


class GPIO:
    class Mode:
        OUTPUT = 'o'
        INPUT = 'i'
        INPUT_PULLUP = 'p'

    def __init__(self, dev, pin, mode):
        self.dev = dev
        self.pin = pin
        dev.send_command("gpio " + str(pin) + " " + str(mode))

    def write(self, value):
        if value:
            self.dev.send_command("gpio " + str(self.pin) + " 1")
        else:
            self.dev.send_command("gpio " + str(self.pin) + " 0")

    def read(self):
        resp = self.dev.send_command_and_read_line("gpio " + str(self.pin))
        if resp[0] == '1':
            return True
        elif resp[0] == '0':
            return False
        else:
            raise RuntimeError('Unexpected value of ' + str(int(resp[0])))


class ADC:
    class Prescaler:
        DIV_2 = 0
        DIV_4 = 2
        DIV_8 = 3
        DIV_16 = 4
        DIV_32 = 5
        DIV_64 = 6
        DIV_128 = 7

    class Reference:
        AREF = 0
        AVcc = 1
        Internal1 = 2
        Internal2 = 3

    class Channel:
        ADC0 = 0
        ADC1 = 1
        ADC2 = 2
        ADC3 = 3
        ADC4 = 4
        ADC5 = 5
        ADC6 = 6
        ADC7 = 7

    def __init__(self, dev, prescaler, reference, ref_voltage):
        self.dev = dev
        self.dev.send_command("an i " + str(prescaler) + " " + str(reference) + " " + str(ref_voltage))

    def select_channel(self, channel):
        self.dev.send_command("an c " + str(channel))

    def read(self):
        self.dev.flush()
        return int(self.dev.send_command_and_read_line("an r"))

    def read_noise_reduction(self):
        return int(self.dev.send_command_and_read_line("an n"))

    def read_voltage(self):
        return float(self.dev.send_command_and_read_line("an v"))

    def disable(self):
        self.dev.send_command("an d")


class AnalogIO:
    class Channel:
        ADC0 = 0
        ADC1 = 1
        ADC2 = 2
        ADC3 = 3
        ADC4 = 4
        ADC5 = 5
        ADC6 = 6
        ADC7 = 7

    def __init__(self, dev, channel):
        self.dev = dev
        self.channel = channel

    def read(self):
        return int(self.dev.send_command_and_read_line("ang r " + str(self.channel)))

    def read_voltage(self):
        return float(self.dev.send_command_and_read_line("ang v " + str(self.channel)))


# -------------------------- I2C ------------------------------------


class I2CMaster:
    def __init__(self, dev):
        self.dev = dev
        dev.send_command("im i")

    def disable(self):
        self.dev.send_command("im d")

    def data_transfer(self, address, data_tx, bytes_to_receive):
        line = self.dev.send_command_and_read_line("im " +
                                                   str(address) +
                                                   " " +
                                                   " ".join(str(i) for i in data_tx) +
                                                   " " +
                                                   str(bytes_to_receive))
        return [int(i) for i in line.split()]


class I2CDevice:
    def __init__(self, dev, address):
        self.address = address
        self.dev = dev

    def data_transfer(self, data_tx, bytes_to_receive):
        line = self.dev.send_command_and_read_line("im " +
                                                   str(self.address) +
                                                   " " +
                                                   " ".join(str(i) for i in data_tx) +
                                                   " " +
                                                   str(bytes_to_receive))
        return [int(i) for i in line.split()]


class I2CSlave:
    def __init__(self, dev, self_address):
        self.dev = dev
        dev.send_command("is i " + str(self_address))

    def disable(self):
        self.dev.send_command("is d")

    def buffer_tx_data(self, data):
        self.dev.send_command("is " + " ".join(str(i) for i in data))

    def read(self):
        line = self.dev.send_command_and_read_line("is r")
        return [int(i) for i in line.split()]

# -------------------------- SPI ------------------------------------


class SPIMaster:
    class Polarity:
        idle_low = 0
        idle_high = 1

    class Phase:
        leading_sample = 0
        trailing_sample = 1

    class DataOrder:
        MSB_first = 0
        LSB_first = 1

    class ClockDivisor:
        DIV_4 = 0
        DIV_16 = 1
        DIV_64 = 2
        DIV_128 = 3

    def __init__(self, dev, polarity, phase, data_order, clock_divisor):
        self.dev = dev
        dev.send_command("spi i " +
                         str(polarity) + " " +
                         str(phase) + " " +
                         str(data_order) + " " +
                         str(clock_divisor))

    def shift(self, data):
        self.dev.send("spi " + " ".join(str(i) for i in data))
        resp = []
        for i in data:
            resp.append(int(self.dev.read()))
        self.dev.cmd_fin()
        return resp

    def disable(self):
        self.dev.send_command("spi d")


class SPIDevice:
    def __init__(self, dev, pin):
        self.dev = dev
        self.pin = pin

    def shift(self, data):
        self.dev.send("spid " + str(self.pin) + " " + " ".join(str(i) for i in data))
        resp = []
        for i in data:
            resp.append(int(self.dev.read()))
        self.dev.cmd_fin()
        return resp


class SPISlave:
    class Polarity:
        idle_low = 0
        idle_high = 1

    class Phase:
        leading_sample = 0
        trailing_sample = 1

    class DataOrder:
        MSB_first = 0
        LSB_first = 1

    def __init__(self, dev, polarity, phase, data_order):
        self.dev = dev
        dev.send_command("ss i " +
                         str(polarity) + " " +
                         str(phase) + " " +
                         str(data_order))

    def buffer_data(self, data):
        self.dev.send_command("ss " + " ".join(str(i) for i in data))

    def read_buffer(self):
        line = self.dev.send_command_and_read_line("ss r")
        return [int(i) for i in line.split()]

    def disable(self):
        self.dev.send("ss d")

# ----------------------- EXAMPLES ----------------------------------


def gpio_example(master, slave):
    a = GPIO(master, 13, GPIO.Mode.OUTPUT)
    b = GPIO(slave, 17, GPIO.Mode.OUTPUT)

    while True:
        b.write(1)
        print a.read(), b.read()

        b.write(0)
        print a.read(), b.read()


def adc_example(master, slave):
    adc = ADC(slave, ADC.Prescaler.DIV_128, ADC.Reference.AVcc, 5)

    analog = AnalogIO(slave, AnalogIO.Channel.ADC0)
    digial = GPIO(slave, 17, GPIO.Mode.OUTPUT)

    while True:
        digial.write(1)
        sleep(0.05)
        high = analog.read_voltage()

        digial.write(0)
        sleep(0.05)
        low = analog.read_voltage()

        print high, low


def spi_example(master, slave):
    spi_master = SPIMaster(master,
                           SPIMaster.Polarity.idle_high,
                           SPIMaster.Phase.leading_sample,
                           SPIMaster.DataOrder.MSB_first,
                           SPIMaster.ClockDivisor.DIV_128)

    spi_device = SPIDevice(master, 10)

    spi_slave = SPISlave(slave,
                         SPISlave.Polarity.idle_high,
                         SPISlave.Phase.leading_sample,
                         SPISlave.DataOrder.MSB_first)

    while True:
        spi_slave.buffer_data([1, 2, 3, 4])
        print "Master got: ", spi_device.shift([10, 11, 12, 13])
        print "Slave got: ", spi_slave.read_buffer()


def i2c_example(master, slave):
    i2c_master = I2CMaster(avr128)
    i2c_dev = I2CDevice(avr128, 0x1E)
    i2c_slave = I2CSlave(avr328, 0x1E)
    sleep(1)
    while True:
        print i2c_dev.data_transfer([1, 2, 3], 0)
        print i2c_slave.read()
        print ""
        sleep(1)

        i2c_slave.buffer_tx_data([10, 11])
        print i2c_dev.data_transfer([4, 5, 6], 2)
        print i2c_slave.read()
        print ""
        sleep(1)

        i2c_slave.buffer_tx_data([100, 50, 25])
        print i2c_dev.data_transfer([], 3)
        print ""


if __name__ == "__main__":
    avr128 = AVRClient('COM34', 115200)
    avr328 = AVRClient('COM9', 250000)
    # gpio_example(avr128, avr328)
    # adc_example(avr128, avr328)
    # i2c_example(avr128, avr328)
    # spi_example(avr128, avr328)
