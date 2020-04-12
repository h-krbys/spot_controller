#ifndef __SPOT_PLANNER_SWAY_H__
#define __SPOT_PLANNER_SWAY_H__

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>

class Sway {
public:
  Sway();
  ~Sway();

  void timerCallback(const ros::TimerEvent &);

private:
  ros::NodeHandle nh;
  ros::Timer      timer;

  ros::Publisher pubJoint;

  // joint angles [rad]
  std_msgs::Float32MultiArray joints;

  int phase;          // move phase

  // time
  const double dt;      // timestep
  double       elapsed; //elapsed time

  double theta;
};

#endif // __SPOT_PLANNER_SWAY_H__