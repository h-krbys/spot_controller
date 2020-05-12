#include "stand.h"

Stand::Stand(){
  pubJoint = nh.advertise<std_msgs::Float32MultiArray>("angle", 1);

  timer = nh.createTimer(ros::Duration(0.01), &Stand::timerCallback, this);

  // initialize joint angles
  joints.data.resize(12);
  for(int i = 0; i < 12; i++) {
    joints.data[i] = 0;
  }
}

Stand::~Stand() {
}

void Stand::timerCallback(const ros::TimerEvent &) {
  for (int i = 0; i < 12; i++) {
    joints.data[i] = 0;
  }
  pubJoint.publish(joints);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "stand");
  Stand stand;
  ros::spin();
}
