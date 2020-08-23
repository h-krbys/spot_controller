#include "servo.h"

Servo::Servo() {
  // Subscribe joint angles
  subJoint = nh.subscribe<std_msgs::Float32MultiArray>("angle", 1, &Servo::jointCallback, this);

  // Set timer
  timer = nh.createTimer(ros::Duration(0.1), &Servo::timerCallback, this);

  // Setup pca9685 (bus, address)
  driver = new PCA9685(1, 0x40);
  driver->setPWMFreq(60);

  // Get joint angle limitations (upper & lower boundary)
  nh.getParam("joint", joint);

  // Initial servo position
  for(int i = 0; i < 12; i++) {
    theta[i] = 0;
  }
}

Servo::~Servo() {
  delete driver;
}

void Servo::jointCallback(const std_msgs::Float32MultiArray::ConstPtr &joint) {
  for(int i = 0; i < 12; i++) {
    theta[i] = joint->data[i];
  }
}

void Servo::timerCallback(const ros::TimerEvent& event){
  for(int i = 0; i < 12; i++) {
    // channel = joint index + 1
    driver->setPWM(static_cast<int>( this->joint[i]["id"] ) + 1, 0,
                   static_cast<int>( this->joint[i]["center"] ) +
                   static_cast<int>( this->joint[i]["direction"] ) * int(450 * theta[i] / 3.14159) );
  }
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "servo");
  Servo servo;
  ros::spin();
}
