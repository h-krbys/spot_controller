#ifndef __SPOT_DRIVER_SERVO_H__
#define __SPOT_DRIVER_SERVO_H__

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include "PCA9685.h"

class Servo {
public:
  Servo();
  ~Servo();

  void jointCallback(const std_msgs::Float32MultiArray::ConstPtr &joy);

private:
  ros::NodeHandle nh;

  ros::Subscriber subJoint;

  PCA9685                    *driver;
  std_msgs::Float32MultiArray joints;
  XmlRpc::XmlRpcValue         limit;
};

#endif // __SPOT_DRIVER_SERVO_H__