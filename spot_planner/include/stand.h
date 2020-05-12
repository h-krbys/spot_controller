#ifndef __SPOT_PLANNER_STAND_H__
#define __SPOT_PLANNER_STAND_H__

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>

class Stand {
public:
  Stand();
  ~Stand();

  void timerCallback(const ros::TimerEvent &);

private:
  ros::NodeHandle nh;
  ros::Timer      timer;

  ros::Publisher pubJoint;

  // joint angles [rad]
  std_msgs::Float32MultiArray joints;

  double theta;
};

#endif // __SPOT_PLANNER_STAND_H__