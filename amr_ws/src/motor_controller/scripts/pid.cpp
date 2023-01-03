#include <math.h>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"

ros::Publisher cmd_vel_pub;
geometry_msgs::Twist cmdVel;

float linear_vel_des=0, linear_vel_act=0, angular_vel=0;
float err=0;

float kp=0.5,ki,kd;
float output=0;

void odomCB(nav_msgs::Odometry odom_msg)
{
  linear_vel_act=odom_msg.twist.twist.linear.x;
}

void controlCB(geometry_msgs::Twist twist_msg)
{
  linear_vel_des=twist_msg.linear.x;
  err = linear_vel_des - linear_vel_act;
  output=linear_vel_act+kp*(err);
  cmdVel.linear.x = output;
  cmd_vel_pub.publish(cmdVel);
}


int main(int argc, char** argv){
  ros::init(argc,argv,"pid_controller");
  ros::NodeHandle n;
  cmd_vel_pub=n.advertise<geometry_msgs::Twist>("cmd_vel",50);
  ros::Subscriber odom_sub=n.subscribe("odom",50,odomCB);
  ros::Subscriber cmd_vel_sub=n.subscribe("cmd_vel_des",50,controlCB);
  //err = linear_vel_des - linear_vel_act;
  //output=linear_vel_act+kp*(err);
  //cmdVel.linear.x = output;
  //cmd_vel_pub.publish(cmdVel);
  ros::spin();
  return 0;
}
