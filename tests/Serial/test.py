import unittest, serial, os, time
from random import random

com = '/dev/ttyUSB0'
ser = serial.Serial(com, 9600, timeout=2)

class Test(unittest.TestCase):
	@classmethod
	def setUpClass(cls):
		pass
		#os.system("make clean flash_default COM=" + com)

	def reboot(self):		
		ser.setDTR(0)
		ser.setDTR(1)

	def setUp(self):
		self.reboot()
		ser.flushInput()

	def test_all_bytes(self):
		for i in xrange(1, 10):
			for chr in xrange(0, 256):
				self.assertEqual(ord(ser.read()), chr)
	
	def test_echo(self):
		time.sleep(2)
		ser.write('0')
		time.sleep(1)
		ser.flushInput()
		for char in xrange(0, 256):
			ser.write(chr(char))
			self.assertEqual(ord(ser.read()), char)

	def test_random_byte(self):
		time.sleep(2)
		ser.write('0')
		time.sleep(1)
		ser.flushInput()
		for repeat in xrange(0, 1000):
			now = int(random()*255)
			ser.write(chr(now))
			self.assertEqual(ord(ser.read()), now)


unittest.main()
