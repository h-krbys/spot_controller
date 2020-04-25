#!/usr/bin/env python

import rospy
from std_msgs.msg import Float32MultiArray
import Adafruit_PCA9685

class Servo:

    def __init__(self):
        # Subscribe 12 joint angles [rad]
        self.sub = rospy.Subscriber("joint", Float32MultiArray, self.jointCallback, queue_size=10)

        # Initialise the PCA9685 using desired address & bus
        self.driver = Adafruit_PCA9685.PCA9685(address = 0x40, busnum = 1)
        self.driver.set_pwm_freq(60)

        # Load joint config from parameter server
        self.limit = rospy.get_param('limit')

    def jointCallback(self, msg):
        print(msg.data[0])
        #self.driver.set_pwm(0, 0, int(self.limit[0]['zero']) + int(450 * msg.data[0] / 3.14159))
        #self.driver.set_pwm(1, 0, int(self.limit[1]['zero']) + int(450 * msg.data[1] / 3.14159))
        #self.driver.set_pwm(2, 0, int(self.limit[2]['zero']) + int(450 * msg.data[2] / 3.14159))
        #self.driver.set_pwm(3, 0, int(self.limit[3]['zero']) + int(450 * msg.data[3] / 3.14159))
        for i in range(12):
            self.driver.set_pwm(i, 0, int(self.limit[i]['zero']) + int(450 * msg.data[i] / 3.14159))
            #self.driver.set_pwm(i, 0, int(self.limit[i]['zero']) + 450) )

if __name__ == '__main__':
    rospy.init_node('servo')
    Servo()
    rospy.spin()
