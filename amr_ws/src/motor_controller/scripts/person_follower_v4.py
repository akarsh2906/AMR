#!/usr/bin/env python3
import rospy
# import math
# import time
from geometry_msgs.msg import Twist
from motor_controller.msg import pfd

MAX_LINEAR_VEL = 0.2
MAX_ANGULAR_VEL = 0.4

LINEAR_MSG = 0
ANGULAR_MSG = 0
STATUS_MSG = 0


def qr_data_callback(qr_data):
    # Get Odom Data
    global LINEAR_MSG, ANGULAR_MSG, STATUS_MSG
    LINEAR_MSG = qr_data.distance
    ANGULAR_MSG = qr_data.angle
    STATUS_MSG = qr_data.status

#rospy.init_node("person_follower_drive")
#rospy.loginfo("Person Follower Has Started.")

#qr_sub = rospy.Subscriber("qr_data", pfd, qr_data_callback)

#cmd_vel_pub = rospy.Publisher("cmd_vel_des", Twist, queue_size=10)
#rate = rospy.Rate(10)
#delay = rospy.Rate(1)

vel_msg =  Twist()

vel_msg.linear.x = 0
vel_msg.angular.z = 0
#time.sleep(2)

    
    
if __name__ == "__main__":
    rospy.init_node("person_follower_drive", anonymous=True)
    #rospy.loginfo("Person Follower Has Started.")
    qr_sub = rospy.Subscriber("qr_data", pfd, qr_data_callback)
    cmd_vel_pub = rospy.Publisher("cmd_vel_des", Twist, queue_size=10)
    if LINEAR_MSG == 1 and ANGULAR_MSG == 1:
        vel_msg.angular.z = -(MAX_ANGULAR_VEL)
        vel_msg.linear.x = MAX_ANGULAR_VEL

    elif LINEAR_MSG == 1 and ANGULAR_MSG == -1:
        vel_msg.angular.z = MAX_ANGULAR_VEL
        vel_msg.linear.x = MAX_ANGULAR_VEL

    elif LINEAR_MSG == 1 and ANGULAR_MSG == 0:
        vel_msg.linear.x = MAX_LINEAR_VEL
        vel_msg.angular.z = 0

    else:
        vel_msg.angular.z = 0
        vel_msg.linear.x = 0

    cmd_vel_pub.publish(vel_msg)
    rospy.spin()
