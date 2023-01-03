#!/usr/bin/env python3
import rospy
# import math
# import time
from geometry_msgs.msg import Twist
from std_msgs.msg import Float32

MAX_LINEAR_VEL = 0.25
MAX_ANGULAR_VEL = 0.5

MIC_DEGREE_MSG = 0
RAD_MSG = 0
ACTUATION_TIME = 0
PI = 3.1415926


def mic_data_callback(mic_data):
    # Get Odom Data
    global MIC_DEGREE_MSG
    MIC_DEGREE_MSG = mic_data 
    rospy.loginfo(MIC_DEGREE_MSG)

if __name__ == "__main__":
    rospy.init_node("sound_follower")
    rospy.loginfo("Sound Follower Has Started.")

    mic_sub = rospy.Subscriber("speaker_angle", Float32, mic_data_callback)

    cmd_vel_pub = rospy.Publisher("cmd_vel", Twist, queue_size=10)
    rate = rospy.Rate(30)
    #delay = rospy.Rate(1)
    vel_msg = Twist()
    vel_msg.linear.x = 0
    vel_msg.angular.z = 0
    #time.sleep(2)
    #rospy.loginfo("MIC_DEGREE_MSG = ", MIC_DEGREE_MSG) 

    while not rospy.is_shutdown():
        try:
            # 1Deg × π/180 = 0.01745Rad
            RAD_MSG = MIC_DEGREE_MSG
            print(RAD_MSG)
            ACTUATION_TIME = RAD_MSG/MAX_ANGULAR_VEL
            vel_msg.angular.z = MAX_ANGULAR_VEL             
            cmd_vel_pub.publish(vel_msg)
            delay = rospy.Rate(1/ACTUATION_TIME)
            delay.sleep()
            #RAD_MSG = 0

            rate.sleep()
        except:
            pass
