#include "sway.h"

Sway::Sway() : dt(0.01) {
  pubJoint = nh.advertise<std_msgs::Float32MultiArray>("angle", 1);

  timer = nh.createTimer(ros::Duration(dt), &Sway::timerCallback, this);

  // initialize joint angles
  joints.data.resize(12);
  for(int i = 0; i < 12; i++) {
    joints.data[i] = 0;
  }

  elapsed = 0.0;
  phase   = 0;

  theta = 0.0;
}

Sway::~Sway() {
}

void Sway::timerCallback(const ros::TimerEvent &) {
  switch (phase) {
  case 0:
    theta += 0.001;
    if(theta > 1) {
      phase = 1;
    }
    break;
  case 1:
    theta -= 0.001;
    if(theta < 0) {
      phase = 0;
    }
    break;
  }

  joints.data[1]  = -theta;
  joints.data[2]  = 2 * theta;
  joints.data[4]  = -theta;
  joints.data[5]  = 2 * theta;
  joints.data[7]  = -theta;
  joints.data[8]  = 2 * theta;
  joints.data[10] = -theta;
  joints.data[11] = 2 * theta;

  elapsed += dt;

  pubJoint.publish(joints);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "sway");
  Sway sway;
  ros::spin();
}