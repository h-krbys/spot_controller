#include "walk.h"

Walk::Walk(){
  subJoint = nh.subscribe<sensor_msgs::JointState>("joint_states", 10, &Walk::jointCallback, this);

  pubJoint = nh.advertise<std_msgs::Float32MultiArray>("angle", 1);

  // initialize joint angles
  joints.data.resize(12);
  for(int i = 0; i < 12; i++) {
    joints.data[i] = 0;
  }
}

Walk::~Walk() {
}

void Walk::jointCallback(const sensor_msgs::JointState::ConstPtr &joint) {
  for(int i = 0; i < 12; i++) {
    joints.data[i] = joint->position[i];
  }

  pubJoint.publish(joints);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "walk");
  Walk walk;
  ros::spin();
}