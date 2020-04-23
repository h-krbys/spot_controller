#include "simulation.h"

Simulation::Simulation() {
  // publish joint angles to RViz
  pubJointState = nh.advertise<sensor_msgs::JointState>("joint_states_source", 1);

  subJoint = nh.subscribe<std_msgs::Float32MultiArray>("joint", 10, &Simulation::jointCallback, this);

  jointState.header.stamp = ros::Time::now();
  jointState.name.resize(12);
  jointState.position.resize(12);

  XmlRpc::XmlRpcValue limit;
  nh.getParam("limit", limit);
  for (int32_t i = 0; i < limit.size(); i++) {
    int         id   = 0;
    std::string name = "";
    if(limit[i]["id"].getType() == XmlRpc::XmlRpcValue::TypeInt) {
      id = static_cast<int>( limit[i]["id"] );
    }
    if(limit[i]["name"].getType() == XmlRpc::XmlRpcValue::TypeString) {
      name = static_cast<std::string>( limit[i]["name"] );
    }
    jointState.name[id]     = name;
    jointState.position[id] = 0.0;
  }
}

Simulation::~Simulation() {
}

void Simulation::jointCallback(const std_msgs::Float32MultiArray::ConstPtr &joint) {
  for (int i = 0; i < 12; i++) {
    jointState.position[i] = joint->data[i];
  }

  pubJointState.publish(jointState);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "simulation");
  Simulation simulation;
  ros::spin();
}