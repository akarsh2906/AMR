#include <math.h>
#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Vector3Stamped.h"


float left_tick=0,l_diff=0;
float right_tick=0,r_diff=0;
double lw_distance=0.0;
double rw_distance=0.0;
double c_distance=0.0;
double theta=0,dtheta;
const double pi=3.141592;
double x=0,y=0,xnew=0,ynew=0;
double speed_x=0,speed_y=0,speed_w=0;

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
        lw_distance=0.000022836*l_diff;
        rw_distance=0.000022836*r_diff;
        c_distance=(lw_distance+rw_distance)/2;
        dtheta=asin((rw_distance-lw_distance)/0.410);
        theta+=dtheta/2;
        if(theta>pi){
            theta-=2*pi;
        }
        else if(theta<-1*pi){
            theta+=2*pi;
        }
        xnew=c_distance*(cos(theta));
        ynew=c_distance*(sin(theta));

        speed_x=xnew/0.05;
        speed_y=ynew/0.05;
        speed_w=dtheta/0.05;
        x+=xnew;
        y+=ynew;
        theta+=dtheta;
        left_tick=tick_msg.vector.x;
        right_tick=tick_msg.vector.y;
        ConstructandPublish(x,y,theta,speed_x,speed_y,speed_w, odom_broadcaster);
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
