#ifndef __SPOT_DRIVER_SERVO_H__
#define __SPOT_DRIVER_SERVO_H__

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include "PCA9685.h"

class Servo {
public:
  Servo();
  ~Servo();

  void jointCallback(const std_msgs::Float32MultiArray::ConstPtr &joint);
  void timerCallback(const ros::TimerEvent &event);

private:
  ros::NodeHandle nh;

  ros::Subscriber subJoint;

  ros::Timer timer;

  PCA9685            *driver;
  XmlRpc::XmlRpcValue joint;
  float               theta[12];
};

#endif // __SPOT_DRIVER_SERVO_H__