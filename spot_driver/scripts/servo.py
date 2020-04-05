#!/usr/bin/python
# -*- coding: utf-8 -*-

#from __future__ import division
#import time

import Adafruit_PCA9685

# Initialise the PCA9685 using desired address and/or bus:
pwm = Adafruit_PCA9685.PCA9685(address = 0x40, busnum = 1)

# Number of servo
servo_num = 12

# Configure min and max servo pulse lengths
servo_min    = 150 # min. pulse length
servo_max    = 600 # max. pulse length
servo_offset = 50

# Set frequency to 60[Hz]
pwm.set_pwm_freq(60)

while True:
    # move servo on each channel
    for i in range(servo_num - 1):
        print('Moving servo on channel: ', i)
        pwm.set_pwm(i, 0, servo_min + servo_offset)
        time.sleep(1)
        pwm.set_pwm(i, 0, servo_max - servo_offset)
        time.sleep(1)
    # move servo on all channel
    for i in range(servo_num - 1):
        print('Moving servo on channel: 0 - 12')
        pwm.set_pwm(i, 0, servo_min + servo_offset)
        time.sleep(1)