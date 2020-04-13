#ifndef __SPOT_INTERFACE_SIMULATION_H__
#define __SPOT_INTERFACE_SIMULATION_H__

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/JointState.h>

class Simulation {
public:
  Simulation();
  ~Simulation();

  void jointCallback(const std_msgs::Float32MultiArray::ConstPtr &joint);

private:
  ros::NodeHandle nh;

  ros::Publisher  pubJointState;
  ros::Subscriber subJoint;

  sensor_msgs::JointState jointState;
  // ???::??? pose;
};

#endif // __SPOT_INTERFACE_SIMULATION_H__