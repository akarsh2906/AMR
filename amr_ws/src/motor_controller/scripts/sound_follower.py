#!/usr/bin/env python3
import rospy
import time
from geometry_msgs.msg import Twist
from std_msgs.msg import Float32

MAX_LINEAR_VEL = 0.25
MAX_ANGULAR_VEL = 1

RAD_MSG = 0
ACTUATION_TIME = 0
PI = 3.14159

def sound_follower():
    if RAD_MSG>PI:
        ACTUATION_TIME = float((2*PI) -RAD_MSG)/MAX_ANGULAR_VEL
        rospy.loginfo(ACTUATION_TIME)
        start = time.time()
        while((time.time() - start) < ACTUATION_TIME):
            print("IN Publish Loop")
            vel_msg.angular.z = -(MAX_ANGULAR_VEL)  
            vel_msg.linear.x = 0           
            cmd_vel_pub.publish(vel_msg)
    else:
        ACTUATION_TIME = float(RAD_MSG)/MAX_ANGULAR_VEL
        start = time.time()
        while((time.time() - start) < ACTUATION_TIME):
            print("IN Publish Loop")
            vel_msg.angular.z = MAX_ANGULAR_VEL  
            vel_msg.linear.x = 0           
            cmd_vel_pub.publish(vel_msg)
        vel_msg.linear.x = 0
    vel_msg.angular.z = 0
    cmd_vel_pub.publish(vel_msg)

def mic_data_callback(mic_data):
    # Get Odom Data
    global RAD_MSG
    RAD_MSG = mic_data.data
    sound_follower()

rospy.init_node("sound_follower")
rospy.loginfo("Sound Follower Has Started.")

mic_sub = rospy.Subscriber("speaker_angle", Float32, mic_data_callback)
cmd_vel_pub = rospy.Publisher("cmd_vel_des", Twist, queue_size=10)
rate = rospy.Rate(30)
vel_msg = Twist()
vel_msg.linear.x = 0
vel_msg.angular.z = 0

if __name__ == "__main__":
        try:

            rospy.spin()
        except:
            pass
