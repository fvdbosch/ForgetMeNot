#!/usr/bin/env python

from rpisoc import *
import time

RPiSoC('SPI')

My_servo = Servo(0, 0.9, 2.1, 0, 120)

My_servo.Start()

My_servo.SetAngle(120)
time.sleep(0.300)
My_servo.SetAngle(0)

#My_servo.Stop()
