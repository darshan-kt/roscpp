#include <ros/ros.h>
#include <std_msgs/Int64.h>
#include <ackermann_msgs/AckermannDriveStamped.h>

class Test
{
    //constructor
    public:
    Test()
    {
      pub = nh.advertise<std_msgs::Int64>("Ardiuno_ino/Acc", 10);
      sub = nh.subscribe("/acker_speed",10, &Test::speedcallback, this);
  
    }
   void speedcallback(const ackermann_msgs::AckermannDriveStamped::ConstPtr& msg)
   {   
    Speed = msg->drive.speed;
   ROS_INFO_STREAM("Speed:"<<Speed);

   Angle = msg->drive.steering_angle;
   ROS_INFO_STREAM("Steering angle:"<<Angle);
   
   std_msgs::Int64 speed_pwm;               //publisher msg_format with object
     
     if ( Speed > min_takeoff_speed && Speed < max_linear_speed){
     float x = (Speed - min_linear_speed) / (max_linear_speed - min_linear_speed);
     speed_pwm.data = min_motor_pwm + (max_motor_pwm - min_motor_pwm) * x;
    //ROS_INFO_STREAM("speed_pwm: " <<speed_pwm.data);
     }
     else if ( Speed > min_linear_speed && Speed < min_takeoff_speed)
     {
     speed_pwm.data = 30;
     }
      else
     {
     speed_pwm.data = 0; 
     }
     pub.publish(speed_pwm); 


     std_msgs::Int64 steering_pulse;   
     if (Angle < max_cw_steering_angle && Angle > min_cw_steering_angle){
       float y = (Angle - min_cw_steering_angle) / (max_cw_steering_angle - min_cw_steering_angle);                  // + angle 0-0.785(45 degree)
       steering_pulse.data = min_cw_pulse + (max_cw_pulse - min_cw_pulse) * y; 
     }

    else if ( Angle < max_ccw_steering_angle && Angle > min_ccw_steering_angle){
    float z = (Angle - 0) / (min_ccw_steering_angle - 0);                  // - angle 0 to -0.785(-45 degree)
    steering_pulse.data = min_ccw_pulse + (max_ccw_pulse - min_ccw_pulse) * z; 
     }

   else
   {
      steering_pulse.data =0;
   }
     pub.publish(steering_pulse); 

     ROS_INFO_STREAM("speed_pwm: " <<speed_pwm.data);
     ROS_INFO_STREAM("steering_pulse: " <<steering_pulse.data);     

   }
     private:
    ros::NodeHandle nh; 
    ros::Publisher pub;
    ros::Subscriber sub;
    double Speed;
    double Angle;
    double x;
    double y;
    double z;
    double min_linear_speed = 0.1;
	  double min_takeoff_speed = 0.81;
	  double max_linear_speed = 1.38;    
    double min_motor_pwm = 1;
	  double max_motor_pwm = 51;
	  double min_cw_steering_angle = 0.1;
	  double max_cw_steering_angle = 0.785;   //radian
	  double min_cw_pulse = 1;
	  double max_cw_pulse = 870;
    double max_ccw_steering_angle = -0.1;
	  double min_ccw_steering_angle = -0.785;
	  double min_ccw_pulse = -1;
	  double max_ccw_pulse = -560;
};


int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "subscribe_and_publish");

  //Create an object of class SubscribeAndPublish that will take care of everything
  Test TestObject;

  ros::spin();

  return 0;
}
