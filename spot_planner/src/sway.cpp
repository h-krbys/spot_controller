#include "sway.h"

Sway::Sway() : dt(0.01) {
  pubJoint = nh.advertise<std_msgs::Float32MultiArray>("joint", 1);

  timer = nh.createTimer(ros::Duration(dt), &Sway::timerCallback, this);

  // initialize joint angles
  joints.data.resize(12);
  for(int i = 0; i < 12; i++) {
    joints.data[i] = 0;
  }

  elapsed = 0.0;
  phase   = 0;
}

Sway::~Sway() {
}

void Sway::timerCallback(const ros::TimerEvent &) {
  switch (phase) {
  case 0:
    joints.data[0] += 0.005;
    printf("joints.data[0] %lf\n", joints.data[0]);
    break;
  case 1:
    break;
  }

  elapsed += dt;

  pubJoint.publish(joints);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "sway");
  Sway sway;
  ros::spin();
}