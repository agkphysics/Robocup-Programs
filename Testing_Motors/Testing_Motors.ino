#include <Scheduler.h>
#include <AccelStepper.h>

AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);


int leftSpeed = 500; //As would be calculated by linefollowing procedure
int rightSpeed = -500; //As would be calculated by linefollowing procedure
boolean runLeftMotor = true;
boolean runRightMotor = true;

//Definition of Movement related functions
long distanceToSteps(long cm)
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

void forward(long cm) {
  leftMotor.move(distanceToSteps(cm));
  rightMotor.move(-distanceToSteps(cm));
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
  forward(20);
  while(motorsRunning()){
    yield();
  }
  delay(1000);
}




void runMotorLoop() {
  leftMotor.run();
  rightMotor.run();  
  yield();
}
