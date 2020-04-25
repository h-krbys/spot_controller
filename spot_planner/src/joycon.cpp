#include "joycon.h"

Joycon::Joycon() {
  // publish joint angles to RViz
  pubJoint = nh.advertise<std_msgs::Float32MultiArray>("joint", 1);

  subJoy = nh.subscribe<sensor_msgs::Joy>("joy", 10, &Joycon::joyCallback, this);

  // initialize joint angles
  joints.data.resize(12);
  for(int i = 0; i < 12; i++) {
    joints.data[i] = 0;
  }
}

Joycon::~Joycon() {
}

void Joycon::joyCallback(const sensor_msgs::Joy::ConstPtr &joy) {
  int direction = 1 - 2 * joy->buttons[REVERSE_BUTTON];
  for (int i = 0; i < 4; i++) {
    joints.data[3 * i + 0] += 0.01 * direction * joy->buttons[JOINT1_BUTTON];
    joints.data[3 * i + 1] += 0.01 * direction * joy->buttons[JOINT2_BUTTON];
    joints.data[3 * i + 2] += 0.01 * direction * joy->buttons[JOINT3_BUTTON];
  }

  pubJoint.publish(joints);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "joycon");
  Joycon joycon;
  ros::spin();
}