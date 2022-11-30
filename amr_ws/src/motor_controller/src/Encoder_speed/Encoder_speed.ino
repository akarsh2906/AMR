#include <ros.h>
#include<SD.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <ros/time.h>

File file;
ros::NodeHandle  nh;

#define LOOPTIME 50

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


geometry_msgs::Vector3Stamped speed_msg;
ros::Publisher speed_pub("speed", &speed_msg);

double speed_act_left = 0;
double speed_act_right = 0;           

void setup() {
  nh.initNode();
  nh.advertise(speed_pub);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(leftEncoderPinA), change_left_a, CHANGE);
  attachInterrupt(digitalPinToInterrupt(leftEncoderPinB), change_left_b, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightEncoderPinA), change_right_a, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightEncoderPinB), change_right_b, CHANGE);
}

void loop() {
  currentMillis = millis();
  Serial.println(currentMillis-prevMillis);
  if (currentMillis - prevMillis >= LOOPTIME){
    prevMillis = currentMillis;


    encoder0Diff = encoder0Pos - encoder0Prev;
    encoder1Diff = encoder1Pos - encoder1Prev;
    
    speed_act_left = encoder0Diff/835.35;     // old = 428.8256                
    speed_act_right = encoder1Diff/835.35;    // old = 428.8256

    encoder0Prev = encoder0Pos;
    encoder1Prev = encoder1Pos; 

  }
  publishSpeed(LOOPTIME);
  nh.spinOnce();
}


//Publish function for odometry, uses a vector type message to send the data (message type is not meant for that but that's easier than creating a specific message type)
void publishSpeed(double time) {
  speed_msg.header.stamp = nh.now();//timestamp for odometry data
  speed_msg.header.stamp.nsec/=1000;
  speed_msg.vector.x = speed_act_left;    //left wheel speed (in m/s)
  speed_msg.vector.y = encoder0Pos;   //right wheel speed (in m/s)
  speed_msg.vector.z = time/1000;         //looptime, should be the same as specified in LOOPTIME (in s)
  speed_pub.publish(&speed_msg);
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
