#include "servo.h"

Servo::Servo() {
  // publish joint angles to RViz
  subJoint = nh.subscribe<std_msgs::Float32MultiArray>("joint", 1, &Servo::jointCallback, this);

  // pca9685 (bus, address)
  driver = new PCA9685(1, 0x40);
  driver->setPWMFreq(60);

  // get joint limit (upper/lower boundary)
  nh.getParam("limit", limit);
}

Servo::~Servo() {
  delete driver;
}

void Servo::jointCallback(const std_msgs::Float32MultiArray::ConstPtr &joint) {
  for(int i = 0; i < 12; i++) {
    driver->setPWM(i, 0, static_cast<int>( limit[i]['zero'] ) + int(450 * joint->data[i] / 3.14159) );
  }
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "servo");
  Servo servo;
  ros::spin();
}