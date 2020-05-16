#include "paw.h"

Paw::Paw() : dt(0.01) {
  pubJoint = nh.advertise<std_msgs::Float32MultiArray>("angle", 1);

  timer = nh.createTimer(ros::Duration(dt), &Paw::timerCallback, this);

  // initialize joint angles
  joints.data.resize(12);
  for(int i = 0; i < 12; i++) {
    joints.data[i] = 0;
  }

  // joint configulation no.1
  theta1[0]  = 0;
  theta1[1]  = -0.7;
  theta1[2]  = 1.76;
  theta1[3]  = 0;
  theta1[4]  = -0.7;
  theta1[5]  = 1.76;
  theta1[6]  = 0;
  theta1[7]  = -0.7;
  theta1[8]  = 1.76;
  theta1[9]  = 0;
  theta1[10] = -0.7;
  theta1[11] = 1.76;
  // joint configulation no.2
  theta2[0] = 0;
  theta2[1] = 0;
  theta2[2] = 2.5;
  for (size_t i = 3; i < 12; i++) {
    theta2[i] = theta1[i];
  }
  // joint configulation no.3
  theta3[0] = 0;
  theta3[1] = 0;
  theta3[2] = 2.0;
  for (size_t i = 3; i < 12; i++) {
    theta3[i] = theta2[i];
  }

  elapsed = 0.0;
  phase   = 0;
  T       = 3;
}

Paw::~Paw() {
}

void Paw::timerCallback(const ros::TimerEvent &) {
  switch (phase) {
  case 0:
    for (int i = 0; i < 12; i++) {
      joints.data[i] = 0 + ( theta1[i] - 0 ) * elapsed / T;
    }
    if(elapsed > T) {
      phase   = 1;
      elapsed = 0;
    }
    break;
  case 1:
    if(elapsed > 0.1) {
      phase   = 2;
      elapsed = 0;
    }
    break;
  case 2:
    for (int i = 0; i < 12; i++) {
      joints.data[i] = theta1[i] + ( theta2[i] - theta1[i] ) * elapsed / T;
    }
    if(elapsed > T) {
      phase   = 3;
      elapsed = 0;
    }
    break;
  case 3:
    if(elapsed > 0.1) {
      phase   = 4;
      elapsed = 0;
    }
    break;
  case 4:
    for (int i = 0; i < 12; i++) {
      joints.data[i] = theta2[i] + ( theta3[i] - theta2[i] ) * elapsed / T;
    }
    if(elapsed > T) {
      phase   = 5;
      elapsed = 0;
    }
    break;
  case 5:
    break;
  }

  elapsed += dt;

  pubJoint.publish(joints);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "paw");
  Paw paw;
  ros::spin();
}
