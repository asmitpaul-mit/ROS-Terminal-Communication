#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>

void chatCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("%s", msg->data.c_str());
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "user2_node");

    ros::NodeHandle nh;

    ros::Publisher chat_pub = nh.advertise<std_msgs::String>("user2_messages", 1000);

    ros::Subscriber chat_sub = nh.subscribe("user1_messages", 1000, chatCallback);

    // ros::Rate loop_rate(10);
    ros::AsyncSpinner spinner(2);

    spinner.start();
    ros::Rate rate(1);

    while (ros::ok())
    {
        std::cout << "Enter message: ";
        std::string message;
        std::getline(std::cin, message);

        std_msgs::String msg;
        msg.data = "Recieved" + message;
        chat_pub.publish(msg);
    }

    return 0;
}