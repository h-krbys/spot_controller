#ifndef __SPOT_PLANNER_WALK_H__
#define __SPOT_PLANNER_WALK_H__

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float32MultiArray.h>

class Walk {
public:
  Walk();
  ~Walk();

  void jointCallback(const sensor_msgs::JointState::ConstPtr &joint);

private:
  ros::NodeHandle nh;

  ros::Subscriber subJoint;
  ros::Publisher  pubJoint;

  // joint angles [rad]
  std_msgs::Float32MultiArray joints;
};

#endif // __SPOT_PLANNER_WALK_H__