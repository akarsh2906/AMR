#include <ros.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <ros/time.h>


#define LOOPTIME 10

#define leftEncoderPinA 18
#define leftEncoderPinB 19

#define rightEncoderPinA 20
#define rightEncoderPinB 21

unsigned long currentMillis;
unsigned long previousArmMillis;
unsigned long previousMillis;

volatile long encoder0Pos = 0;    // encoder 1
volatile long encoder1Pos = 0;    // encoder 2

ros::NodeHandle nh;

geometry_msgs::Vector3Stamped speed_msg;
ros::Publisher speed_pub("speed", &speed_msg);

void setup()
{
  nh.initNode();
  nh.advertise(speed_pub);
  
  pinMode(leftEncoderPinA, INPUT_PULLUP);
  pinMode(leftEncoderPinB, INPUT_PULLUP);

  pinMode(rightEncoderPinA, INPUT_PULLUP); 
  pinMode(rightEncoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(leftEncoderPinA), doEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(leftEncoderPinB), doEncoderB, CHANGE); 

  attachInterrupt(digitalPinToInterrupt(rightEncoderPinA), doEncoderC, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightEncoderPinB), doEncoderD, CHANGE);
}

void loop()
{
  currentMillis = millis();   // bookmark the time 
  if (currentMillis - previousMillis >= 10) {  // start timed loop for everything else
         previousMillis = currentMillis;
         /*Serial.print(encoder0Pos);
         Serial.print(",");
         Serial.println(encoder1Pos);*/
  } 

  speed_msg.vector.x = encoder0Pos;
  speed_msg.vector.y = encoder1Pos;
  speed_pub.publish(&speed_msg);
  //publishSpeed(LOOPTIME);
  nh.spinOnce();
}
/*
void publishSpeed(double time) {
  speed_msg.header.stamp = nh.now();      //timestamp for odometry data
  speed_msg.vector.x = encoder0Pos;    //left wheel speed (in m/s)
  //speed_msg.vector.y = speed_act_right;   //right wheel speed (in m/s)
  //speed_msg.vector.z = time/1000;         //looptime, should be the same as specified in LOOPTIME (in s)
  speed_pub.publish(&speed_msg);
//  nh.loginfo("Publishing odometry");
}
*/

// ************** encoders interrupts **************

// ************** encoder 1 *********************


void doEncoderA(){  

  if (digitalRead(leftEncoderPinA) == HIGH) { 
    if (digitalRead(leftEncoderPinB) == LOW) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else                                
  { 
    if (digitalRead(leftEncoderPinB) == HIGH) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
 
}

void doEncoderB(){  

  if (digitalRead(leftEncoderPinB) == HIGH) {   
    if (digitalRead(leftEncoderPinA) == HIGH) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else { 
    if (digitalRead(leftEncoderPinA) == LOW) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
  

}

// ************** encoder 2 *********************

void doEncoderC(){  

  if (digitalRead(rightEncoderPinA) == HIGH) { 
    if (digitalRead(rightEncoderPinB) == LOW) {  
      encoder1Pos = encoder1Pos - 1;         // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;         // CCW
    }
  }
  else                                    
  { 
    if (digitalRead(rightEncoderPinB) == HIGH) {   
      encoder1Pos = encoder1Pos - 1;          // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;          // CCW
    }
  }
 
}

void doEncoderD(){  

  if (digitalRead(rightEncoderPinB) == HIGH) {   
    if (digitalRead(rightEncoderPinA) == HIGH) {  
      encoder1Pos = encoder1Pos - 1;         // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;         // CCW
    }
  }
  else { 
    if (digitalRead(rightEncoderPinA) == LOW) {   
      encoder1Pos = encoder1Pos - 1;          // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;          // CCW
    }
  }
  

}
