#include <ros/ros.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <std_msgs/Int64.h>

float Speed;
float Angle;
void speedCallback(const ackermann_msgs::AckermannDriveStamped::ConstPtr& msg){
   //Using the callback function just for subscribing  
   //Subscribing the message coming on above msg_format, access it using msg object and storing it in 'speed' variable
   Speed = msg->drive.speed;
   ROS_INFO_STREAM("Speed:"<<Speed);

   Angle = msg->drive.steering_angle;
   ROS_INFO_STREAM("Steering angle:"<<Angle);

}

int main(int argc, char **argv){
  ros::init(argc, argv, "speed_converter");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("/acker_speed",1000,&speedCallback);
  ros::Publisher pub = nh.advertise<std_msgs::Int64>("Ardiuno_ino/Acc", 1000);
  ros::Rate rate(2);

  while(ros::ok()){
     std_msgs::Int64 speed_pwm;               //publisher msg_format with object
     
     if ( 0.81 < Speed && Speed < 1.38){
     float x = (Speed - 0) / (1.38 - 0);
     speed_pwm.data = 0 + (51 - 0) * x;
    //ROS_INFO_STREAM("speed_pwm: " <<speed_pwm.data);
     }
     else if (0.1 < Speed && Speed < 0.81)
     {
     speed_pwm.data = 30;
     }
      else
     {
    //  /* (updated scale) max_speed=1.38m/s(speed range 0-1.38) and speed_pwm range betwn 0-51
    //  Formula: (mapping the values)
    //  x = (inValue - minInRange) / (maxInRange - minInRange);   invalue= entered speed, minInrange(speed)=0, maxInrRange=1.38 m/s
    //  result = minOutRange + (maxOutRange - minOutRange) * x     minOutRange(speed_pwm)=0, maxOutRange=51
    //  */

          speed_pwm.data = 0; 
      }
     pub.publish(speed_pwm); 
     ROS_INFO_STREAM("speed_pwm: " <<speed_pwm.data);

     std_msgs::Int64 steering_pulse;   
     if (0.785 < Angle && Angle > 0){
       float y = (Angle - 0) / (0.785 - 0);                  // + angle 0-0.785(45 degree)
       steering_pulse.data = 0 + (870 - 0) * y; 
     }

      else if (0 < Angle > -0.785){
       float z = (Angle - 0) / (-0.785 - 0);                  // - angle 0 to -0.785(-45 degree)
       steering_pulse.data = 0 + (-560 - 0) * z; 
     }

   else
   {
      steering_pulse.data =0;
   }
      pub.publish(steering_pulse); 
      ROS_INFO_STREAM("steering_pulse: " <<steering_pulse.data);     

      rate.sleep();
      ros::spinOnce();      //Notice this
  } 
}
