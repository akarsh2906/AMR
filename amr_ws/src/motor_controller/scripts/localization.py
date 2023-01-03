#!/usr/bin/env python3
import rospy
import math
import time
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from std_srvs.srv import Empty


MAX_LINEAR_VEL = 0.25
MAX_ANGULAR_VEL = 1

NO_OF_ROTATIONS = 4

quat_x = None
quat_y = None 
quat_z = None 
quat_w = None

rot_counter = 0

def call_localization_service():
    rospy.wait_for_service('global_localization')
    call_global_localization = rospy.ServiceProxy('global_localization',Empty)
    call_global_localization()

def odom_callback(odom_data):
    # Get Odom Data
    global x_coordinate,y_coordinate, quat_x, quat_y, quat_z, quat_w
    x_coordinate = odom_data.pose.pose.position.x
    y_coordinate = odom_data.pose.pose.position.y
    quat_x = odom_data.pose.pose.orientation.x
    quat_y = odom_data.pose.pose.orientation.y
    quat_z = odom_data.pose.pose.orientation.z
    quat_w = odom_data.pose.pose.orientation.w

def qua_2_euler(x,y,z,w):
    t0 = +2.0 * (w * x + y * z)
    t1 = +1.0 - 2.0 * (x * x + y * y)
    X  = math.degrees(math.atan2(t0,t1))

    t2 = +2.0 * (w * y - z * x)
    t2 = +1.0 if t2 > +1.0 else t2
    t2 = -1.0 if t2 < -1.0 else t2
    Y  = math.degrees(math.asin(t2))

    t3 = +2.0 * (w * z + x * y)
    t4 = +1.0 - 2.0 * (y * y + z * z)
    Z  = math.degrees(math.atan2(t3,t4))

    return X,Y,Z

if __name__ == "__main__":
    rospy.init_node("localizer")
    rospy.loginfo("Global Localization Has Started.")

    cmd_vel_pub = rospy.Publisher("cmd_vel", Twist, queue_size=10)
    rate = rospy.Rate(30)
    delay = rospy.Rate(1)

    odom_sub =  rospy.Subscriber("odom", Odometry, odom_callback)
    vel_msg =  Twist()

    vel_msg.linear.x = 0
    vel_msg.angular.z = 0.25
    #time.sleep(2)

    #rosservice.call_service('/global_localization',True)
    call_localization_service()

    while not rospy.is_shutdown():
        
        try:
            vel_msg.angular.z = MAX_ANGULAR_VEL
            cmd_vel_pub.publish(vel_msg)
            o_x, o_y, o_z = qua_2_euler(quat_x,quat_y,quat_z,quat_w)

            if rot_counter == NO_OF_ROTATIONS:
                break
            if round(o_z) > -10 and round(o_z) < 10:
                rot_counter= rot_counter + 1
                time.sleep(2)

            print(rot_counter)
            print(round(o_z))

            rate.sleep()

        except:
            pass

    vel_msg.angular.z = 0
    cmd_vel_pub.publish(vel_msg)

