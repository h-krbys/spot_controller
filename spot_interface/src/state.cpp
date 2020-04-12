#include "state.h"

State::State() {
  pubJointState = nh.advertise<sensor_msgs::JointState>("joint_states_source", 1);

  subJoint = nh.subscribe<std_msgs::Float32MultiArray>("joint", 10, &State::jointCallback, this);

  jointState.header.stamp = ros::Time::now();
  jointState.name.resize(12);
  jointState.position.resize(12);

  XmlRpc::XmlRpcValue joint_config;
  nh.getParam("joint_config", joint_config);
  for (int32_t i = 0; i < joint_config.size(); i++) {
    int         id   = 0;
    std::string name = "";
    if(joint_config[i]["id"].getType() == XmlRpc::XmlRpcValue::TypeInt) {
      id = static_cast<int>( joint_config[i]["id"] );
    }
    if(joint_config[i]["name"].getType() == XmlRpc::XmlRpcValue::TypeString) {
      name = static_cast<std::string>( joint_config[i]["name"] );
    }
    jointState.name[id]     = name;
    jointState.position[id] = 0.0;
  }
}

State::~State() {
}

void State::jointCallback(const std_msgs::Float32MultiArray::ConstPtr &joint) {
  for (int i = 0; i < 12; i++) {
    jointState.position[i] = joint->data[i];
  }

  pubJointState.publish(jointState);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "state");
  State state;
  ros::spin();
}