import serial, sys, io, threading
from time import sleep

DEBUG = False

class Slave:
    def __init__(self, com, speed=115200):
        self.serial = serial.Serial(com, speed, timeout=10)
        self.ser_io = io.TextIOWrapper(io.BufferedRWPair(self.serial, self.serial, 1),
                                       newline='\r',
                                       line_buffering=True)
        self.wait_for_null()
        print "Connected!"
        self.flush()
        self.send("ping 1 2 3")
        print self.read()
        self.cmd_fin()
        # print self.serial.readline()

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
        s = self.ser_io.readline().replace('\x00','')
        if DEBUG:
            print "readed: ", s
        return s

    def flush(self):
        self.serial.flushInput()
        self.serial.flushOutput()

    def wait_for_null(self):
        while self.serial.read(1) != '\0':
            pass

    def cmd_fin(self):
        self.wait_for_null()


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
        dev.send_command("spis i " +
                         str(polarity) + " " +
                         str(phase) + " " +
                         str(data_order))

    def buffer_data(self, data):
        self.dev.send("spis " + " ".join(str(i) for i in data))
        resp = []
        for i in data:
            resp.append(int(self.dev.read()))
        self.dev.cmd_fin()
        return resp

    def disable(self):
        self.dev.send("spis d")


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
        self.dev.send("gpio " + str(self.pin) + " r")
        resp = self.dev.serial.read(1)
        self.dev.cmd_fin()
        if resp[0] == '1':
            return True
        else:
            return False


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

def resp_slave(spi_slave, resp):
    resp.extend(spi_slave.buffer_data([100, 101, 102, 103, 104, 105]))

if __name__ == "__main__":
    slave = Slave('COM9', 250000)
    master = Slave('COM34', 115200)
    # adc = ADC(slave, ADC.Prescaler.DIV_128, ADC.Reference.AVcc, 5)
    # a.select_channel(ADC.Channel.ADC0)

    spi = SPIMaster(master,
                    SPIMaster.Polarity.idle_high,
                    SPIMaster.Phase.leading_sample,
                    SPIMaster.DataOrder.MSB_first,
                    SPIMaster.ClockDivisor.DIV_128)

    device = SPIDevice(master, 10)

    spis = SPISlave(slave,
                    SPISlave.Polarity.idle_high,
                    SPISlave.Phase.leading_sample,
                    SPISlave.DataOrder.MSB_first)
    while True:
        resp = []
        t = threading.Timer(0, resp_slave, [spis, resp])
        t.start()
        sleep(0.01)

        print "M:", device.shift([0, 1, 2, 3, 4, 5])
        print "S:", resp

        # t = threading.Timer(0, resp_slave, [spis])
        # t.start()
        # sleep(0.01)
        # print spi.shift([0, 1, 2, 3, 4, 5])
    # ch0 = AnalogIO(slave, AnalogIO.Channel.ADC0)
    # dio = GPIO(slave, 17, GPIO.Mode.OUTPUT)
    #
    # while True:
    #     dio.write(1)
    #     sleep(0.05)
    #     high = ch0.read_voltage()
    #     dio.write(0)
    #     sleep(0.05)
    #     low = ch0.read_voltage()
    #     print high, low

        # b = GPIO(slave, 17, GPIO.Mode.OUTPUT)

        # for i in range(100):
        #     b.write(1)
        #     if not b.read() or not a.read():
        #         print "FAIL"
        #
        #     b.write(0)
        #     if a.read() or b.read():
        #         print "FAIL"
