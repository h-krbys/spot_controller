#!/usr/bin/env python

import rospy
from std_msgs.msg import Float32MultiArray
import Adafruit_PCA9685

class Servo:

    def __init__(self):
        # Subscribe 12 joint angles [rad]
        self.sub = rospy.Subscriber("joint", Float32MultiArray, self.jointCallback)
        # Initialise the PCA9685 using desired address & bus
        # self.driver = Adafruit_PCA9685.PCA9685(address = 0x40, busnum = 1)
        #
        # self.driver.set_pwm_freq(60)
        self.device_config = rospy.get_param('/device_config')

    def jointCallback(self, msg):
        for i in range(12):
            print('Moving servo on channel: ', i, ', angle: ', msg.data[i])
            # self.driver.set_pwm(i, 0, msg.data[i])

if __name__ == '__main__':
    rospy.init_node('servo')
    Servo()
    rospy.spin()