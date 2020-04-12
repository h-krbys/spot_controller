#include "state.h"

State::State() {
  pubJointState = nh.advertise<sensor_msgs::JointState>("joint_states_source", 1);
}

State::~State() {
}

void State::jointCallback(const sensor_msgs::JointState &joint) {
  pubJointState.publish(joint_state);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "state");
  State state;
  ros::spin();
}