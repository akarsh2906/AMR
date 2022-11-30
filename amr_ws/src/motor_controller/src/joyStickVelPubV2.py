#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist

import pygame
from pygame import joystick
from pygame.locals import *

LEFT_TRIGGER = 2
RIGHT_TRIGGER = 5
LEFT_STICK_LR = 0
LEFT_STICK_UP = 1
RIGHT_STICK_LR = 3
RIGHT_STICK_UP = 4
DEADZONE = 0.11


pygame.init()
joystick.init()
#pygame.display.init()
#pygame.display.set_mode((400,400))

joysticks = [joystick.Joystick(i) for i in range(pygame.joystick.get_count())]

xbox = joystick.Joystick(0)
xbox.init()


if __name__ == "__main__":
    rospy.init_node("joystickVelPub")
    rospy.loginfo("Joystick Has Started.")

    pub = rospy.Publisher("cmd_vel", Twist, queue_size=10)
    rate = rospy.Rate(20)
    delay = rospy.Rate(2)

    msg = Twist()
    msg.linear.x = 0
    msg.angular.z = 0

    while not rospy.is_shutdown():
        for event in pygame.event.get(): pass
           # if event.type == QUIT:
           #     pygame.quit()
           #     exit()

        print("Right Trigger \t =", xbox.get_axis(RIGHT_TRIGGER)+1)
        print("Left Trigger \t =", xbox.get_axis(LEFT_TRIGGER)+1)
        print("Right Stick LR\t =", xbox.get_axis(RIGHT_STICK_LR))
        print("Right Stick UP\t =", xbox.get_axis(RIGHT_STICK_UP))  
        print("Left Stick LR\t =", xbox.get_axis(LEFT_STICK_LR))
        print("Left Stick UP\t =", xbox.get_axis(LEFT_STICK_UP))
        # if(msg.angular.z < 0.05 or msg.angular.z > -0.05):
        #     msg.angular.z = 0

        msg.linear.x = 0.15*(xbox.get_axis(RIGHT_TRIGGER)+1) - 0.15*(xbox.get_axis(LEFT_TRIGGER)+1)
        
        if(xbox.get_axis(LEFT_STICK_LR) > DEADZONE or xbox.get_axis(LEFT_STICK_LR) < -DEADZONE):
            msg.angular.z = -(xbox.get_axis(LEFT_STICK_LR))
        else:
            msg.angular.z = 0

        rospy.loginfo(f" x = {msg.linear.x}")
        rospy.loginfo(f" z = {msg.angular.z}")

        






        

        pub.publish(msg)
        rate.sleep()
