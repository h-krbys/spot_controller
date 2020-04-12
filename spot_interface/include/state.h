#ifndef __SPOT_INTERFACE_STATE_H__
#define __SPOT_INTERFACE_STATE_H__

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

class State {
public:
  State();
  ~State();

  void jointCallback(const sensor_msgs::JointState &joint);

private:
  ros::NodeHandle nh;

  ros::Publisher pubJointState;

  sensor_msgs::JointState joint_state;
};

#endif // __SPOT_INTERFACE_STATE_H__