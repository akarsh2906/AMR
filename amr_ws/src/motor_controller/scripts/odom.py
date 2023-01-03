#!/usr/bin/env python3

import rospy
import math

from geometry_msgs.msg import Quaternion
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from tf.broadcaster import TransformBroadcaster
from std_msgs.msg import Float32

rospy.init_node("odom_publihser")

wheel_diameter = 0.150
wheel_sep = 0.4
Nl,Nr=0.0,0.0
rate = 10.0
base_frame_id = 'base_link'
odom_frame_id = 'odom'

x=0
y=0
th=0
dx=0
dr=0
x0=0
y0=0
t0 = 0.0
t1 = 0.0
dist = 0
d = 0
linear_vel = 0.0
ang_vel = 0.0
theta = 0


def left_cb(msg):
    global Nl
    Nl = msg.data

def right_cb(msg):
    global Nr
    Nr = msg.data

def in_range(angle):
    angle = math.degrees(angle)
#	print(angle)
    if angle>180:
#	print("in range: ",180-angle)
        return 180-angle
    elif angle<-180:
#	print("in range: ",-180-angle)
        return -180-angle
    else:
#	print("in range: ",angle)
        return angle




def odom_update():
    global then,t_next,wheel_diamter,Nl,Nr,wheel_sep,dx,dr,th,x,y,base_frane_id,odom_frame_id,now,x0,y0,dist,t0,t1,d,theta
    global linear_vel,ang_vel
    dl = math.pi*wheel_diameter*Nl
    dr = math.pi*wheel_diameter*Nr
    d = (dr+dl)/2
    theta = math.radians(in_range((dl-dr)/wheel_sep))
    #print(math.degrees(theta))
    x = d*math.cos(theta)
    y = -d*math.sin(theta)
    t0 = rospy.Time.now().to_sec()
    if abs(d-dist)!=0:
        t1 = rospy.Time.now().to_sec()
        linear_vel = (d-dist)/(abs(t1-t0)*1000)
#		print("in else")
#		print("speed",linear_vel)
#		print("time",abs(t1-t0)*1000)
        dist =d
    if abs(th-theta)!=0:
        t2 = rospy.Time.now().to_sec()
        ang_vel = (theta-th)/(abs(t2-t0)*1000)
#		print("in else")
#		print("speed",ang_vel)
#		print("time",abs(t2-t0)*1000)
        th=theta

    quaternion = Quaternion()
    quaternion.x = 0.0
    quaternion.y = 0.0
    quaternion.z = math.sin( theta / 2 )
    quaternion.w = math.cos( theta / 2 )
    odom_broadcaster.sendTransform((x, y, 0),(quaternion.x, quaternion.y, quaternion.z, quaternion.w),rospy.Time.now(),base_frame_id,odom_frame_id)
    odom = Odometry()
    odom.header.frame_id = odom_frame_id
    odom.pose.pose.position.x = x
    odom.pose.pose.position.y = y
    odom.pose.pose.position.z = 0
    odom.pose.pose.orientation = quaternion
    odom.child_frame_id = base_frame_id
    odom.twist.twist.linear.x = linear_vel
    odom.twist.twist.linear.y = 0
    odom.twist.twist.angular.z = ang_vel
    odom_pub.publish(odom)

if __name__ == '__main__':

    rospy.Subscriber("left_ticks", Float32, left_cb)
    rospy.Subscriber("right_ticks", Float32, right_cb)
    odom_pub = rospy.Publisher("odom", Odometry, queue_size=10)
    odom_broadcaster = TransformBroadcaster()
    while not rospy.is_shutdown():
        odom_update()
        rospy.sleep(0.001)
