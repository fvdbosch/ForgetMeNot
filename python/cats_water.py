#!/usr/bin/env python

from rpisoc import *  
import time

RPiSoC('SPI')

led = DigitalOutput(12,4)

for i in (0, 1):
	led.Write(1)
	time.sleep(2.0)
	led.Write(0)
