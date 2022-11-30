#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <AccelStepper.h>
#include <ros/time.h>

const int leftStep = 5;
const int leftDir = 4;
const int rightStep = 7;
const int rightDir = 6;

float vl=0;
float vr=0;
float linear_vel=0;
float angular_vel=0;


AccelStepper leftstepper(AccelStepper::DRIVER, leftStep, leftDir);
AccelStepper rightstepper(AccelStepper::DRIVER, rightStep, rightDir);


ros::NodeHandle nh;


void callbackSetBothVelocities(const geometry_msgs::Twist& twist)
{
  linear_vel = linear_vel+(0.02*twist.linear.x);
  angular_vel = angular_vel+(0.1*twist.angular.z);
  vl = linear_vel - (angular_vel*0.205);
  vr = linear_vel + (angular_vel*0.205);
  leftstepper.setSpeed(vl*16751);
  rightstepper.setSpeed(vr*16751);
  //Serial.println(vl);
}


ros::Subscriber<geometry_msgs::Twist> subVelocities("/turtle1/cmd_vel", callbackSetBothVelocities);

void setup()
{
  Serial.begin(57600);
  leftstepper.setMaxSpeed(12000);
  rightstepper.setMaxSpeed(12000);
  nh.initNode();
  nh.subscribe(subVelocities);
  
}

void loop()
{
  leftstepper.runSpeed();
  rightstepper.runSpeed();
  nh.spinOnce();
}
