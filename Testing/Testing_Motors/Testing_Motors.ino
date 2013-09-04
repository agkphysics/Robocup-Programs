#include <Scheduler.h>
#include <AccelStepper.h>

AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);


float leftSpeed = 500.0; //Initial Speed (for testing purposes)
float rightSpeed = 500.0; //Initial Speed (for testing purposes)
boolean runLeftMotor = true;
boolean runRightMotor = true;

//Definition of Movement related functions
long cmToSteps(float cm)
{
  return (long)((cm * 1600.0)/(6.46 * 3.14159265358979));
}

boolean motorsRunning() {
  if (leftMotor.distanceToGo() != 0 || rightMotor.distanceToGo() != 0) {
    return true;
  }
  else {
    return false;
  }
}

void straight(float cm) {
  leftMotor.move(cmToSteps(cm));
  rightMotor.move(-cmToSteps(cm));
}

void rotate(float deg) {//positive rotates Right, negative rotates Left
  leftMotor.move(cmToSteps((deg/360.0)*3.14159265358979*13.75)); //Note that 13.99 is the 'diameter' that gives the most accurate movement for a 360 rotate
  rightMotor.move(cmToSteps((deg/360.0)*3.14159265358979*13.75));
}

void swingWithRight (float deg) { //Positive turns LEFT!!!  Negative turns RIGHT!!! (going backwards)
  leftMotor.move(0);
  rightMotor.move(-cmToSteps((deg/360.0)*3.14159265358979*13.75*2));
}

void swingWithLeft(float deg) {//Positive turns Right, Negative turns Left (going backwards)
  rightMotor.move(0);
  leftMotor.move(cmToSteps((deg/360.0)*3.14159265358979*13.75*2));
}

void setup()
{
  pinMode(13, OUTPUT); // For the led 
  digitalWrite(13, HIGH); //Flashing LED once, could be removed later
  delay(500);
  digitalWrite(13, LOW);
  leftMotor.setMaxSpeed(900);
  rightMotor.setMaxSpeed(900);
  leftMotor.setAcceleration(10000);
  rightMotor.setAcceleration(10000);

  leftMotor.setSpeed(leftSpeed);//Must be set once to allow movement, setSpeed(float) should be called after moveTo, not needed to be called after move()
  rightMotor.setSpeed(rightSpeed);//Must be set once to allow movement

  //leftMotor.move(1600);
  //rightMotor.move(-1600);
 
 Scheduler.startLoop(runMotorLoop);




  straight(10000);
 
}

void setMotorSpeeds() {
  if (leftSpeed > 0) {
    leftMotor.move(1000000);
    leftMotor.setSpeed(leftSpeed);
  }
  else if (leftSpeed < 0) {
    leftMotor.move(-1000000);
    leftMotor.setSpeed(leftSpeed);
  }
  else {
    leftMotor.move(0);
    leftMotor.setSpeed(0);
  }
  
  if (rightSpeed > 0) {
    rightMotor.move(-1000000);
    rightMotor.setSpeed(-rightSpeed);
  }
  else if (rightSpeed < 0) {
    rightMotor.move(1000000);
    rightMotor.setSpeed(-rightSpeed);
  }
  else {
    rightMotor.move(0);
    rightMotor.setSpeed(0);
  }
}

void loop()
{

  setMotorSpeeds();
  if (leftSpeed > 0 || rightSpeed >0) {
    leftSpeed = leftSpeed-1;
    rightSpeed = rightSpeed-1;
  }
  delay(10);
}

void runMotorLoop() {
  leftMotor.run();
  rightMotor.run();  
  yield();
}




/* Gridlock 1
  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  swingWithLeft(45.0);
  while(motorsRunning()) yield();
  straight(17.0);
  while(motorsRunning()) yield();
  rotate(-90.0);
  while(motorsRunning()) yield();
  straight(40.0);
  while(motorsRunning()) yield();
  rotate(90.0);
  while(motorsRunning()) yield();
  straight(17.0);
  while(motorsRunning()) yield();
  swingWithRight(45);
  while(motorsRunning()) yield();
  delay(5000);
  */
