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

        # Publish joint angles to RViz
        self.pub = rospy.Publisher('joint_states_source', JointState, queue_size=10)

        # self.joints = JointState()
        # self.joints.header = Header()
        # self.joints.header.stamp = rospy.Time.now()
        # self.joints.name = [
        # front_left_shoulder, front_left_leg, front_left_foot, front_right_shoulder, front_right_leg, front_right_foot,
        # rear_left_shoulder, rear_left_leg, rear_left_foot, rear_right_shoulder, rear_right_leg, rear_right_foot]
        # self.joints.position = [3, 0.5418, -1.7297, -3.1017]
        # self.joints.velocity = []
        # self.joints.effort = []
        # pub.publish(self.joints)

        joints = rospy.get_param('/joint')

    def jointCallback(self, msg):
        for i in range(12):
            print('Moving servo on channel: ', i, ', angle: ', msg.data[i])
            # self.driver.set_pwm(i, 0, msg.data[i])

if __name__ == '__main__':
    rospy.init_node('servo')
    Servo()
    rospy.spin()