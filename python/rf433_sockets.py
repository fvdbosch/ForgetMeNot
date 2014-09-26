#!/usr/bin/env python

import smbus  
import sys  
  
bus = smbus.SMBus(1)  
address = 38  
  
house = int(sys.argv[1])  
unit = int(sys.argv[2])  
on = int(sys.argv[3])  
  
bus.write_byte(address, house)  
bus.write_byte(address, unit)  
bus.write_byte(address, on)

