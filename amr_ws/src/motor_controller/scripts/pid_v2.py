#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry

LINEAR_VEL_DES = None
LINEAR_VEL_ACT = None
ANGUALAR_VEL_DES = None
ANGUALAR_VEL_ACT = None
ANGUALAR_VEL = None
ERR_LINEAR = None
ERR_ANGULAR= None
KP_LINEAR = 0.5
KP_ANGULAR = 0.5
KI = None
KD = None
OUTPUT_LINEAR = None
OUTPUT_ANGULAR = None


def odomCB(odom_msg):
    global LINEAR_VEL_ACT, ANGUALAR_VEL_ACT
    LINEAR_VEL_ACT = odom_msg.twist.twist.linear.x
    ANGUALAR_VEL_ACT = odom_msg.twist.twist.angular.z

def controlCB(twist_msg):
    global LINEAR_VEL_DES, ANGUALAR_VEL_DES
    LINEAR_VEL_DES = twist_msg.linear.x
    ANGUALAR_VEL_DES = twist_msg.angular.z

    ERR_LINEAR = LINEAR_VEL_DES - LINEAR_VEL_ACT
    ERR_ANGULAR = ANGUALAR_VEL_DES - ANGUALAR_VEL_ACT
    OUTPUT_LINEAR = LINEAR_VEL_ACT + (KP_LINEAR*ERR_LINEAR)
    OUTPUT_ANGULAR = ANGUALAR_VEL_ACT +(KP_ANGULAR*ERR_ANGULAR)
    vel_msg.linear.x = OUTPUT_LINEAR
    vel_msg.angular.z = OUTPUT_ANGULAR
    cmd_vel_pub.publish(vel_msg)

rospy.init_node("pid_controller")
rospy.loginfo("PID Controller Has Started.")

cmd_vel_pub = rospy.Publisher("cmd_vel", Twist, queue_size=10)
rate = rospy.Rate(10)
#delay = rospy.Rate(1)

odom_sub =  rospy.Subscriber("odom", Odometry, odomCB)
cmd_vel_des_sub = rospy.Subscriber("cmd_vel_des", Twist, controlCB)

vel_msg =  Twist()
vel_msg.linear.x = 0
vel_msg.angular.z = 0

if __name__ == "__main__":        
    try:
        rospy.spin()
     
    except:
        pass
