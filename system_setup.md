
# Welcome to Alpha-X Autonomous mobile robot repository!

Hi! This repository contains all the instructions and files required to configure the Alpha-X **AMR**


## Remote PC Setup

A PC will be used for visualizing the tasks performed by the AMR such as autonomous navigation.

### 1. Ubuntu 20.04
Install the Desktop image of Ubuntu 20.04 on your remote PC by downloading the image below and following the normal installation process.
[Ubuntu 20.04 Desktop Image](https://releases.ubuntu.com/focal/ubuntu-20.04.5-desktop-amd64.iso)
### 2. ROS Noetic Installation
ROS is used to run RViz visualization by communicating with the AMR System. Follow the instructions mentioned on the [ROS Noetic installation page](http://wiki.ros.org/noetic/Installation/Debian) to install and configure ROS on your PC.
### 3. RViz Configuration
Create a workspace consisting of one package in order to launch RViz simulator with required configuration.
Navigate to your home directory and create a folder as your workspace:

    cd ~/
    mkdir -p catkin_ws/src

Enter the directory and build:

    cd catkin_ws/
    catkin_make

Head in to the src folder and then create a ROS package

    cd src/
    catkin_create_pkg alpha_rviz rospy
Inside the package, create a launch folder and an rviz folder:

    cd alpha_rviz/
    mkdir launch
    mkdir rviz

Navigate into the launch folder and create a launch file named **alpha_rviz.launch**:

    cd launch/
    nano alpha_rviz.launch
Open the launch file using gedit and paste the following into the file and save.

    <launch>
      <node type="rviz" name="rviz" pkg="rviz" args="-d $(find my_robot_controller)/rviz/AMR_rvizconfig2.rviz" />
    </launch>
Now, the launch file specifies the name of the config file i.e. "**AMR_rvizconfig2.rviz**". This needs to be placed in the **config** folder we created earlier. You can find this file in "**amr_ws/src/motor_controller/rviz/**" location of this repository.

And that is it for the setup regarding the remote PC!

## AMR System Setup
The controller used for the AMR is the [Nvidia Jetson Nano 4gb](https://developer.nvidia.com/embedded/jetson-nano-developer-kit).
This board is responsible for the actual execution of ROS Navigation Stack which consists of several custom written scripts and also a few ready ROS packages. In this section we will see the process to setup the Jetson Nano.
### 1. Ubuntu 20.04
Nvidia Jetson Nano doesn't have official support for Ubuntu 20.04 as it requires JetPack 5.0 as a minimum however the Jetson Nano supports upto JetPack 4, hence we will install a custom image called XUbuntu 20.04.
You can download the image and install the OS onto your jetson nano by refering to the following link:
 [Xubuntu 20.04 Focal Fossa L4T R32.3.1 - Custom Image for the Jetson Nano](https://forums.developer.nvidia.com/t/xubuntu-20-04-focal-fossa-l4t-r32-3-1-custom-image-for-the-jetson-nano/121768)
### 2. ROS Noetic Installation
ROS is used to implement the ROS Navigation Stack which enables the robot to navigate autonomously. Follow the instructions mentioned on the [ROS Noetic installation page](http://wiki.ros.org/noetic/Installation/Debian) to install and configure ROS on your Jetson Nano..

### 2. ROS Packages installation
There are several packages which are used collectively and this forms the Navigation Stack. The packages thar we must install are:

 - map_server
 - move_base
 - amcl
 - global_planner
 - dwa_local_planner

Run the following commands on your Jetson Nano to install all the required packages.

    sudo apt update
    sudo apt-get install ros-noetic-move-base ros-noetic-amcl ros-noetic-map-server ros-noetic-global-planner ros-noetic-dwa-local-planner
