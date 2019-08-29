
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

'''
Comman syntax for creating any kind of node using c++
1.write a main function with arguments
int main()
{
2.Initialize the ros node (follow ros node syntax)
3.Initilize the ros nodehandle (follow ros nodehandle syntax)
4.Initialize the publisher/subscriber (follow publisher/subscriber syntax)

This above actions should be continously run untill ros master died, so use while loop for continous running.
5.Syntax for while loop 
int count=0;
while()
{
publish actions
Info actions
//c_str() converts a C++ string into a C-style, You use it when you want to pass a C++ string into a function that expects a C-style string.
}
return 0;
}
'''


int main(int argc, char **argv)
{
ros::init(argc, argv, "boss");
ros::NodeHandle n;
ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

ros::Rate loop_rate(10);

int cout=0;
while (ros::ok())
{
std_msgs::String msg;
std::stringstream ss;
ss<<"hello world"<<count;
msg.data =ss.str();

ROS_INFO("%s", msg.data.c_str());

chatter_pub.publish(msg);
ros::spinOnce();
loop_rate.sleep();
++count;
}
return 0;
}
