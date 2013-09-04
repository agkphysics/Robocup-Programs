// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 

void rotate(int targetAngle, int speedFactor) 
{ 
  int pos = 0;    // variable to store the servo position 
  while(pos
  for(pos = 0; pos < targetAngle; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(101 - speedFactor);                       // waits 15ms for the servo to reach the position 
  }  
}
 
 
   while(_pos<100){
    Gripper.write(_pos);
    _pos++;
    delay(30);
  }
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  rotate(90, 50);
} 
 
 

void loop() {
  
}
