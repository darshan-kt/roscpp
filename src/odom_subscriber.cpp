 
/*

 #include "ros/ros.h"
 #include "name_of_package/msg_format.h"


void callback_function(const name_of_package::msg_format::constPtr&, variable_to_store_msg_information)
{
	double varible_to_access_field_of_msg_data = variable_to_store_msg_information->top_level_field.next_fied.end_data;
	ROS_INFO("varible_to_access_field_of_msg_data: %f", varible_to_access_field_of_msg_data);
}
int main(int argc, char** argv)
{
	ros::init(argc, argv, "name_of_node");
	ros::NodeHandle nh;
	ros::Subscriber sub=nh.subscribe("name_of_topic, queue_size, callback_function")
	ros::spin();
	return 0;

}

*/

#include<ros/ros.h>
#include<nav_msgs/Odometry.h>


void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
	double linear_x = msg->pose.pose.position.x;
	double angular_z = msg->pose.pose.orientation.z;
	ROS_INFO("linear_x = %f", "angular_z = %f", linear_x, angular_z);
}

int main(int argc, char** argv){
	ros::init(argc, argv, "location_info");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("odom", 10, OdomCallback);
	ros::spin();
	return 0;
}
