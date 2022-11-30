#include <ros.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <ros/time.h>


ros::NodeHandle  nh;

#define LOOPTIME 10

#define leftEncoderPinA 18
#define leftEncoderPinB 19

#define rightEncoderPinA 20
#define rightEncoderPinB 21

volatile long encoder0Pos = 0;    // encoder 1
volatile long encoder1Pos = 0;    // encoder 2

unsigned long currentMillis;
unsigned long prevMillis;

float encoder0Diff;
float encoder1Diff;

float encoder0Prev;
float encoder1Prev;



geometry_msgs::Vector3Stamped right_speed_msg;                          //create a "right_speed_msg" ROS message
geometry_msgs::Vector3Stamped left_speed_msg;                           //create a "leftspeed_msg" ROS message


ros::Publisher right_speed_pub("right_speed", &right_speed_msg);        //create a publisher to ROS topic "right speed" using the "speed_msg" type
ros::Publisher left_speed_pub("left_speed", &left_speed_msg);           //create a publisher to ROS topic "left speed" using the "speed_msg" type


double speed_act_left = 0;                    //Actual speed for left wheel in m/s
double speed_act_right = 0;                    //Command speed for left wheel in m/s  

void setup() {
  nh.initNode();
  nh.advertise(right_speed_pub);            //prepare to publish right speed in ROS topic
  nh.advertise(left_speed_pub);             //prepare to publish left speed in ROS topic
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


    encoder0Diff = encoder0Pos - encoder0Prev; // Get difference between ticks to compute speed
    encoder1Diff = encoder1Pos - encoder1Prev;
    
    speed_act_left = encoder0Diff/628.2794;     // old = 428.8256                
    speed_act_right = encoder1Diff/628.2794;    // old = 428.8256

    encoder0Prev = encoder0Pos; // Saving values
    encoder1Prev = encoder1Pos;
  

  }
  publishRightSpeed(LOOPTIME);
  publishLeftSpeed(LOOPTIME);
  
  nh.spinOnce();
}


//Publish function for odometry, uses a vector type message to send the data (message type is not meant for that but that's easier than creating a specific message type)

void publishRightSpeed(double time) {
  right_speed_msg.header.stamp = nh.now();      //timestamp for odometry data
  right_speed_msg.vector.x = speed_act_right;   //right wheel speed (in m/s)
  right_speed_msg.vector.y = 0;                 //Direction not considered
  right_speed_msg.vector.z = time/1000;         //looptime, should be the same as specified in LOOPTIME (in s)
  right_speed_pub.publish(&right_speed_msg);
//  nh.loginfo("Publishing odometry");
}

void publishLeftSpeed(double time) {
  left_speed_msg.header.stamp = nh.now();      //timestamp for odometry data
  left_speed_msg.vector.x = speed_act_left;    //left wheel speed (in m/s)
  left_speed_msg.vector.y = 0;                 //Direction not considered
  left_speed_msg.vector.z = time/1000;         //looptime, should be the same as specified in LOOPTIME (in s)
  left_speed_pub.publish(&left_speed_msg);
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
