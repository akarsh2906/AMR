#include <math.h>
#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Vector3Stamped.h"


float left_tick=0,l_diff=0;
float right_tick=0,r_diff=0;
double th=0,delta_th=0;
const double pi=3.141592;
double x=0,y=0,delta_x=0,delta_y=0;
double vx=0,vy=0,vth=0;
double v_left=0,v_right=0;	

//boost::shared_ptr<tf::TransformBroadcaster> transform_ptr;
//tf::TransformBroadcaster odom_broadcaster;
ros::Publisher odom_pub;
ros::Time current_time,prev_time;
nav_msgs::Odometry odom;


void ConstructandPublish(double xx,double yy,double ww,double spx,double spy,double spz, tf::TransformBroadcaster br){
    
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(ww);
    
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_footprint";
    odom_trans.transform.translation.x = xx;
    odom_trans.transform.translation.y = yy;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;
    br.sendTransform(odom_trans);
    
    odom.header.stamp=current_time;
    odom.header.frame_id="odom";
    odom.pose.pose.position.x=xx;
    odom.pose.pose.position.y=yy;
    odom.pose.pose.position.z=0.0;
    odom.pose.pose.orientation=odom_quat;

    odom.child_frame_id="base_footprint";
    odom.twist.twist.linear.x=spx;
    odom.twist.twist.linear.y=spy;
    odom.twist.twist.angular.z=spz;
    odom_pub.publish(odom);
}


void tickCB(geometry_msgs::Vector3Stamped tick_msg){
    current_time=ros::Time::now();
    static tf::TransformBroadcaster odom_broadcaster;
    if((current_time-prev_time).toSec()>=0.05){
        prev_time=current_time;
        l_diff=tick_msg.vector.x - left_tick;
        r_diff=tick_msg.vector.y - right_tick;
        
        v_left=(l_diff*0.000022836)/0.05;
        v_right=(r_diff*0.000022836)/0.05;
        
        vx = ((v_right + v_left) / 2);
        vy = 0;
        vth = ((v_right - v_left)/0.410);
        
        delta_x = (vx * cos(th)) * 0.05;
        delta_y = (vx * sin(th)) * 0.05;
        delta_th = vth * 0.05;

        x += delta_x;
        y += delta_y;
        th += delta_th;
        
        left_tick=tick_msg.vector.x;
        right_tick=tick_msg.vector.y;
        
        ConstructandPublish(x,y,th,vx,vy,vth, odom_broadcaster);
    }
}


int main(int argc, char** argv){
  ros::init(argc,argv,"odometry_publisher");
  ros::NodeHandle n;
  //transform_ptr.reset(new tf::TransformBroadcaster);
  odom_pub=n.advertise<nav_msgs::Odometry>("odom",50);
  ros::Subscriber tick_sub=n.subscribe("motors_ticks",100,tickCB);
  ros::spin();
  return 0;
}
