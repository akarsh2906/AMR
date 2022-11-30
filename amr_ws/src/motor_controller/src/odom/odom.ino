#include <ros.h>
#include <ros/time.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>

ros::NodeHandle  nh;

#define LOOPTIME 10

#define leftEncoderPinA 18
#define leftEncoderPinB 19

#define rightEncoderPinA 20
#define rightEncoderPinB 21

volatile long encoder0Pos = 0;
volatile long encoder1Pos = 0;

unsigned long currentMillis;
unsigned long prevMillis;

float encoder0Diff;
float encoder1Diff;

float encoder0Prev;
float encoder1Prev;

float x=0;
float y=0;
float phi=0;
float x_new=0;
float y_new=0;
float phi_new=0;
float Dl=0;
float Dr=0;
float Dc=0;
float speed_x=0;
float speed_y=0;
float speed_w=0;
const double pi=3.141592;

geometry_msgs::Quaternion odom_quat;

nav_msgs::Odometry odom_msg;
geometry_msgs::TransformStamped odom_trans;
ros::Publisher odom_pub("odom", &odom_msg);
tf::TransformBroadcaster odom_broadcaster;

//double speed_act_left = 0;
//double speed_act_right = 0;

void setup() {
  nh.initNode();
  nh.advertise(odom_pub);
//  Serial.begin(115200);

  
//  Serial.println("Basic Encoder Test:");
  attachInterrupt(digitalPinToInterrupt(leftEncoderPinA), change_left_a, CHANGE);
  attachInterrupt(digitalPinToInterrupt(leftEncoderPinB), change_left_b, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightEncoderPinA), change_right_a, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightEncoderPinB), change_right_b, CHANGE);
}

void loop() {
  currentMillis = millis();
  if (currentMillis - prevMillis >= LOOPTIME){
    prevMillis = currentMillis;


    encoder0Diff = encoder0Pos - encoder0Prev;
    encoder1Diff = encoder1Pos - encoder1Prev;
    
    //speed_act_left = encoder0Diff/628.2794;             
    //speed_act_right = encoder1Diff/628.2794;

    Dl = 0.022836*encoder0Diff;
    Dr = 0.022836*encoder1Diff;
    Dc = (Dl+Dr)/2;

    
    phi_new = asin((Dr-Dl)/0.410);
    phi=phi_new/2+phi;
    if(phi>pi){
      phi-=2*pi;
    }
    else if(phi<-1*pi){
      phi+=2*pi;
    }
    x_new = (Dc*(cos(phi)));
    y_new = (Dc*(sin(phi))); 

    speed_x = x_new/LOOPTIME;
    speed_y = y_new/LOOPTIME;
    speed_w = phi_new/LOOPTIME;

    x+=x_new;
    y+=y_new;
    //phi+=phi_new;

    odom_quat = tf::createQuaternionFromYaw(phi);
    
    encoder0Prev = encoder0Pos;
    encoder1Prev = encoder1Pos;
  
  }
  
  publishOdom(LOOPTIME);
  nh.spinOnce();
}


//Publish function for odometry, uses a vector type message to send the data (message type is not meant for that but that's easier than creating a specific message type)
void publishOdom(double time) {
  odom_trans.header.stamp = nh.now();
  odom_trans.header.frame_id = "odom";
  odom_trans.child_frame_id = "base_link";
  odom_trans.transform.translation.x = x;
  odom_trans.transform.translation.y = y;
  odom_trans.transform.translation.z = 0.0;
  odom_trans.transform.rotation = odom_quat;
  odom_broadcaster.sendTransform(odom_trans);

  odom_msg.header.stamp = nh.now();
  odom_msg.header.frame_id = "odom";

  odom_msg.pose.pose.position.x = x;
  odom_msg.pose.pose.position.y = y;
  odom_msg.pose.pose.position.z = 0.0;
  odom_msg.pose.pose.orientation = odom_quat;
  odom_msg.child_frame_id = "base_link";
  odom_msg.twist.twist.linear.x = speed_x;
  odom_msg.twist.twist.linear.y = speed_y;
  odom_msg.twist.twist.angular.z = speed_w;
  odom_pub.publish(&odom_msg);

//  nh.loginfo("Publishing odometry");
}


// ************** encoders interrupts **************

// ************** encoder 1 *********************


void change_left_a(){  

  // look for a low-to-high on channel A
  if (digitalRead(leftEncoderPinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(leftEncoderPinB) == LOW) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(leftEncoderPinB) == HIGH) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
 
}

void change_left_b(){  

  // look for a low-to-high on channel B
  if (digitalRead(leftEncoderPinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(leftEncoderPinA) == HIGH) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(leftEncoderPinA) == LOW) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
  

}

// ************** encoder 2 *********************

void change_right_a(){  

  // look for a low-to-high on channel A
  if (digitalRead(rightEncoderPinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(rightEncoderPinB) == LOW) {  
      encoder1Pos = encoder1Pos - 1;         // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(rightEncoderPinB) == HIGH) {   
      encoder1Pos = encoder1Pos - 1;          // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;          // CCW
    }
  }
 
}

void change_right_b(){  

  // look for a low-to-high on channel B
  if (digitalRead(rightEncoderPinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(rightEncoderPinA) == HIGH) {  
      encoder1Pos = encoder1Pos - 1;         // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(rightEncoderPinA) == LOW) {   
      encoder1Pos = encoder1Pos - 1;          // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;          // CCW
    }
  }
  

}
