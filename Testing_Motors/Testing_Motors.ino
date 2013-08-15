#include <Scheduler.h>
#include <AccelStepper.h>

AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);


int leftSpeed = 500; //As would be calculated by linefollowing procedure
int rightSpeed = -500; //As would be calculated by linefollowing procedure
boolean runLeftMotor = true;
boolean runRightMotor = true;

double distanceToSteps(double dist)
{
  return (dist * 100) / (30.25 * 3.14159265358979);
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

  leftMotor.move(-500);
  rightMotor.move(500);
 
 Scheduler.startLoop(runMotorLoop);

 
}


void loop()
{

  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
}

void runMotorLoop() {
  if (runLeftMotor == true) {
    leftMotor.run();
    if (leftMotor.distanceToGo () == 0) {
      runLeftMotor==false;
    }
  }
  
    if (runRightMotor == true) {
      rightMotor.run();
      if (rightMotor.distanceToGo () == 0) {
        runRightMotor==false;
      }
    }
  
  yield();
}
