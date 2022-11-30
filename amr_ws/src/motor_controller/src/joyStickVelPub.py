#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist

import pygame
from pygame import joystick
from pygame.locals import *


pygame.init()
joystick.init()

joysticks = [joystick.Joystick(i) for i in range(pygame.joystick.get_count())]

xbox = joystick.Joystick(0)
xbox.init()


if __name__ == "__main__":
    rospy.init_node("joystickVelPub")
    rospy.loginfo("Joystick Has Started.")

    pub = rospy.Publisher("/turtle1/cmd_vel", Twist, queue_size=10)
    rate = rospy.Rate(20)
    delay = rospy.Rate(2)

    msg = Twist()
    msg.linear.x = 0
    msg.angular.z = 0

    while not rospy.is_shutdown():
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                exit()

        if xbox.get_button(0):
            rospy.loginfo("Backward")
            msg.linear.x = -0.2
            msg.angular.z = 0

        elif xbox.get_button(3):
            rospy.loginfo("Forward")
            msg.linear.x = 0.2
            msg.angular.z = 0

        elif xbox.get_button(1):
            rospy.loginfo("Right")
            msg.angular.z = 1.0

        elif xbox.get_button(2):
            rospy.loginfo("Left")
            msg.angular.z = -1.0

        else:
            msg.linear.x -= 0.5
            if(msg.linear.x < 0.05):
                msg.linear.x = 0
                delay.sleep()

        	#msg.linear.x = 0
        	#msg.angular.z -= 0.05
            #elif(msg.angular.z < 0.05):
                #msg.angular.z = 0
                #delay.sleep()
	     

        pub.publish(msg)
        rate.sleep()
