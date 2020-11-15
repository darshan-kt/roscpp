#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Point.h>
#include <string.h>
#include <stdio.h>

using namespace std;

double g_z_height = 1.5;
bool g_trigger = true;

void init_marker_vals(visualization_msgs::Marker &marker){
 //Marker related params means each marker should contains below attributes
	marker.header.frame_id = "world";
	marker.header.stamp = ros::Time();
	// marker.ns = "my_namespace";
	marker.id = 0;
	marker.type = visualization_msgs::Marker::SPHERE_LIST;
	// marker.action = visualization_msgs::Marker::ADD;
	marker.pose.orientation.x = 0.0;
	marker.pose.orientation.y = 0.0;
	marker.pose.orientation.z = 0.0;
	marker.pose.orientation.w = 0.0;
	marker.scale.x = 0.02;
	marker.scale.y = 0.02;
	marker.scale.z = 0.02;
	marker.color.a = 1.0;
	marker.color.r = 2.0;
	marker.color.g = 5.0;
	marker.color.b = 0.0;
}

int main(int argc, char **argv){
	ros::init(argc, argv, "marker_testing");
	ros::NodeHandle nh;
	ros::Publisher vis_pub = nh.advertise<visualization_msgs::Marker>("marker_topic", 0);
	visualization_msgs::Marker marker; //instatiate a marker object
	geometry_msgs::Point point; //points will be used to specify where the markers go

	init_marker_vals(marker);   //to fill the marker attributes

	double z_des;
	//build a wall of markers; set range and resolution
	double x_min = -1.0;
	double x_max = 1.0;
	double y_min = -1.0;
	double y_max = 1.0;
	double dx_des = 0.01;
	double dy_des = 0.01;

	while(ros::ok()) {
		if (g_trigger){
			z_des = g_z_height;
			ROS_INFO("Construction plane of markers at height %f", z_des);
			marker.header.stamp = ros::Time();
			marker.points.clear();  //clear out this vector

			for (double x_des = x_min; x_des < x_max; x_des += dx_des){
				for (double y_des = y_min; y_des < y_max; y_des += dy_des) {
					point.x = x_des;
					point.y = y_des;
					point.z = z_des;
					marker.points.push_back(point);
				}
			}
		}
		ros::Duration(0.1).sleep();
		vis_pub.publish(marker);
		ros::spinOnce();
	}
	return 0;
}