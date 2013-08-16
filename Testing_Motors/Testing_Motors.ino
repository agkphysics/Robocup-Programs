#include <Scheduler.h>
#include <AccelStepper.h>

AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);


int leftSpeed = 500; //Initial Speed (for testing purposes)
int rightSpeed = -500; //Initial Speed (for testing purposes)
boolean runLeftMotor = true;
boolean runRightMotor = true;

//Definition of Movement related functions
long cmToSteps(long cm)
{
  return (cm * 1600)/(6.46 * 3.14159265358979);
}

boolean motorsRunning() {
  if (leftMotor.distanceToGo() != 0 || rightMotor.distanceToGo() != 0) {
    return true;
  }
  else {
    return false;
  }
}

void straight(long cm) {
  leftMotor.move(cmToSteps(cm));
  rightMotor.move(-cmToSteps(cm));
}

void rotate(long deg) {//positive rotates Right, negative rotates Left
 // long rotationCm = ((deg/360)*3.14159265358979*13.25);
  leftMotor.move(cmToSteps((deg/360)*3.14159265358979*13.7));
  rightMotor.move(cmToSteps((deg/360)*3.14159265358979*13.7));
}




void setup()
{
  pinMode(13, OUTPUT); // For the led 
  digitalWrite(13, HIGH); //Flashing LED once, could be removed later
  delay(500);
  digitalWrite(13, LOW);
  leftMotor.setMaxSpeed(600);
  rightMotor.setMaxSpeed(600);
  leftMotor.setAcceleration(10000);
  rightMotor.setAcceleration(10000);

  leftMotor.setSpeed(leftSpeed);//Must be set once to allow movement, setSpeed(float) should be called after moveTo, not needed to be called after move()
  rightMotor.setSpeed(rightSpeed);//Must be set once to allow movement

  //leftMotor.move(1600);
  //rightMotor.move(-1600);
 
 Scheduler.startLoop(runMotorLoop);



 
}


void loop()
{
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  rotate(360);
  while(motorsRunning()) yield();
  delay(1000);
}




void runMotorLoop() {
  leftMotor.run();
  rightMotor.run();  
  yield();
}
