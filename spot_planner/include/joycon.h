#ifndef __SPOT_PLANNER_JOYCON_H__
#define __SPOT_PLANNER_JOYCON_H__

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/Joy.h>

#define GAIN 0.0001
#define JOINT1_BUTTON 4
#define JOINT2_BUTTON 7
#define JOINT3_BUTTON 6
#define REVERSE_BUTTON 14

class Joycon {
public:
  Joycon();
  ~Joycon();

  void joyCallback(const sensor_msgs::Joy::ConstPtr &joy);

private:
  ros::NodeHandle nh;

  ros::Publisher  pubJoint;
  ros::Subscriber subJoy;

  std_msgs::Float32MultiArray joints;
  XmlRpc::XmlRpcValue         joint;
};

#endif // __SPOT_PLANNER_JOYCON_H__