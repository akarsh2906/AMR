
# Alpha-X AMR Navigation

This page will let us know how to perform Autonomous Navigation on the Alpha-X AMR


##  Setup workspace
Firstly, move to the home directory of your jetson nano by running the following command in the terminal:

    cd ~/

Now we need to clone all the contents of this repository onto the nano. We can do this with the following command:

    git clone https://github.com/akarsh2906/AMR.git
Navigate to the workspace called "amr_ws":

    cd AMR/amr_ws/

Now we need to delete the build directory as it is the folder created when you use catkin_make to build your workspace, however the contents of the build folder change with a different system, hence we delete the folder and build the whole workspace again which will create a new and correct build folder. Run the following command in the terminal:

    rm -rf build/
Build the workspace again:

    catkin_make

Now all the packages are built and the nodes are ready to be executed!
## ROS Master setup
Since we are using two different systems, we need the data from the AMR into the Remote PC for visualization and also for setting intial position estimates as well as goal positions for the robot. Hence, we need to have one single ROS Master communication with both the systems and in order to achieve this, **we must have both the systems connected to the same network**.

On your **remote PC**, open the terminal and and type `ifconfig`. This will tell you the IP address assigned to the remote PC as shown below:

Now in the terminal itself, run the command `nano .bashrc` and scroll down to the bottom of the bash script, here we will add two lines:

    export ROS_MASTER_URI=http://192.168.1.101:11311
    export ROS_HOSTNAME=192.168.1.101

This sets the remote PC and the master.
Now we will repeat the process in the **Jetson Nano**, first, open the terminal and run `ifconfig`. Check the IP address assigned to the Jetson Nano. In the same terminal, run `nano ~/.bashrc` and scroll down to the bottom.
Add the following two lines:

    export ROS_MASTER_URI=http://192.168.1.101:11311
    export ROS_HOSTNAME=192.168.1.102
As we can see, the IP address of the ROS_MASTER_URI stays the same but the ROS_HOSTNAME changes to the IP of the Jetson Nano.

Let's see if this has worked, open a new terminal in your **PC** and type `roscore` and hit enter. Now head on to the **Jetson Nano** and open a new terminal and type `rostopic list` and hit enter, we should see that it lists two topics.

If we see these two topics in the Jetson Nano, then it means that the connection is successful and the now the Remote PC is the master and Jetson Nano is the slave.

## Let's Start the Navigation
Now that we have the repository contents and the ROS Master setup, we are ready to start launching nodes.
### 1. Mapping
Place the robot in a closed environment, now open a new terminal on the remote PC and start `roscore`.
Open a new terminal on the Jetson Nano and run the command:

    roslaunch motor_controller alpha_bringup.launch
This starts the drive of the robot and also odometry and transform feedback begins. The bringup also starts the Lidar and IMU.
Now, open another terminal in the Jetson Nano, and run the following command:

    roslaunch hector_slam_launch tutorial.launch
Open a new terminal in the Remote PC and run the following command:

    roslaunch alpha_rviz alpha_rviz.launch

This will launch the Rviz simulator and we can see the map being created.

Open a new terminal in the Remote PC and run the following command:

    rosrun teleop_twist_keyboard teleop_twist_keyboard
Through this node, we can control the robot manually using the keys mentioned in the terminal. Manually move around the robot throughout the closed environment until the full map is created as seen in the RViz window.
We can now stop the processes in all the terminals and close them.

### 2. Navigation
Place the robot in a the environment used previously for mapping, now open a new terminal on the remote PC and start `roscore`.
Open a new terminal on the Jetson Nano and run the command:

    roslaunch motor_controller alpha_bringup.launch
Now, open another terminal in the Jetson Nano, and run the following command:

    roslaunch motor_controller alpha_navigation.launch
This launch file launches all the nodes necessary for autonomous navigation i.e.

    map_server
    move_base
    amcl
Open a new terminal in the Remote PC and run the following command:

    roslaunch alpha_rviz alpha_rviz.launch

This will launch the Rviz simulator and we can see the map that has already been created.
![enter image description here](https://imagehost9.online-image-editor.com/oie_upload/images/8143535C34fV/yBWx1OgKuyWw.png)

![enter image description here](https://imagehost9.online-image-editor.com/oie_upload/images/8143535C34fV/yBWx1OgKuyWw.png)
