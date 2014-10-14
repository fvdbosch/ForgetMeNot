#!/usr/bin/env python

from rpisoc import *
import sys 

RPiSoC('SPI')

My_DutyCycle = sys.argv[1]

My_PWM = PWM(1) # Port 3 Pin 1
My_PWM.Start()
My_PWM.WritePeriod(65535)

try:
    My_DutyCycle = int(My_DutyCycle)
    
    if(My_DutyCycle >= 0 and My_DutyCycle <= 100):
        # Inside boundaries, set passed value
        print "Inside boundaries, set passed value"
        My_PWM.SetDutyCycle(My_DutyCycle)
    
    else:
        # Outside boundaries, turn off
        print "Outside boundaries, turn off"
        My_PWM.SetDutyCycle(0)
    
except ValueError:
    # Invalid value, turn off
    print "Invalid value, turn off"
    My_PWM.SetDutyCycle(0)

        