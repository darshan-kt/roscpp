#include <ros/ros.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <std_msgs/Int64.h>

double speed;
void speedCallback(const ackermann_msgs::AckermannDriveStamped::ConstPtr& msg){
   //Using the callback function just for subscribing  
   //Subscribing the message coming on above msg_format, access it using msg object and storing it in 'speed' variable
   speed = msg->drive.speed;
   ROS_INFO_STREAM("Speed:"<<speed);

}

int main(int argc, char **argv){
  ros::init(argc, argv, "speed_converter");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("/acker_speed",1000,&speedCallback);
  ros::Publisher pub = nh.advertise<std_msgs::Int64>("Ardiuno_ino/Acc", 1000);
  ros::Rate rate(2);

  while(ros::ok()){
     std_msgs::Int64 pwm;               //publisher msg_format with object

     /*  max_speed=0.75m/s(speed range 0-0.75) and pwm range betwn 0-255
     Formula: (mapping the values)
     x = (inValue - minInRange) / (maxInRange - minInRange);   invalue= entered speed, minInrange(speed)=0, maxInrRange=0.75 m/s
     result = minOutRange + (maxOutRange - minOutRange) * x     minOutRange(pwm)=0, maxOutRange=255
     */

     float x = (speed - 0) / (0.75 - 0);
     pwm.data = 0 + (255 - 0) * x;
     ROS_INFO_STREAM("pwm: " <<pwm.data);
     pub.publish(pwm);   //This line is for publishing. It publishes to 'Ardiuno_ino/Acc' 
     rate.sleep();
     ros::spinOnce();      //Notice this
 
