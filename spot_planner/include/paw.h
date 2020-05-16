#ifndef __SPOT_PLANNER_PAW_H__
#define __SPOT_PLANNER_PAW_H__

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>

class Paw {
public:
  Paw();
  ~Paw();

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
  double       T;       // time for each motion

  // joint configulation
  double theta1[12], theta2[12], theta3[12];
};

#endif // __SPOT_PLANNER_PAW_H__