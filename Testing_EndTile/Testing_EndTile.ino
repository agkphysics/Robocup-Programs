#include <Servo.h>
#include <Scheduler.h>
#include <Compass.h>
#include <Wire.h>
#include <Motors.h>
#include <Ultrasonic.h>
#include <AccelStepper.h>

AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);
Motors motors(leftMotor, rightMotor);
Servo closeArm;

Ultrasonic ultrasonic(11, 12);

Compass compass;
float initialHeading;

void endTile(boolean left)
{
  initialHeading = compass.heading();
  
  motors.setMaxSpeeds(500, 500);
  motors.straight(0.0);
  
  if (left) motors.rotate(-90.0);
  motors.wait();
  
  motors.setMaxSpeeds(100, 100);
  
  motors.rotate(90.0);
  float dist = 60.0;
  float headingToCan = 0.0;
  while (true)
  {
    /* Search for can */
    while (motors.running())
    {
      float currentDist = ultrasonic.distance();
      if (currentDist < dist)
      {
        headingToCan = compass.heading();
        dist = currentDist;
      }
      yield();
    }
    if (dist <= 50.0) break;
    else
    {
      dist = 60.0;
      headingToCan = 0.0;
      
      motors.setMaxSpeeds(500, 500);
      motors.rotate(-90);
      motors.wait();
      motors.setMaxSpeeds(50, 50);
      motors.rotate(90.0);
    }
  }
  float finishHeading = compass.heading();
  
  motors.setMaxSpeeds(500, 500);

  while (abs(compass.heading() - headingToCan) > 2.0)
  {
    motors.rotate(-1.0);
    motors.wait();
  }
  
  /* An extra few degrees just in case... */
  if (dist >= 40.0) motors.rotate(-13.0);
  else motors.rotate(-8.0);
  motors.wait();
  
  float distToCan = dist;
  motors.straight(distToCan);
  motors.wait();
  
  /* Swing to the right in case the can is too far right */
  if (dist >= 40.0) motors.swingWithLeft(30.0);
  else motors.swingWithLeft(45.0);
  motors.wait();
  delay(250);
  
  closeArm.write(0); // MUST be 0, not 180!
  delay(750);
  
  /* Lift arm */
  digitalWrite(2, HIGH);
  delay(2000);
  digitalWrite(2, LOW);
  
  if (dist >= 40.0) motors.swingWithLeft(-30.0);
  else motors.swingWithLeft(-45.0);
  motors.wait();
  motors.straight(-distToCan);
  motors.wait();
  if (left) motors.rotate(-10.0);
  else motors.rotate(10.0);
  
  if (left)
  {
    while (abs(compass.heading() - initialHeading) > 2.0)
    {
      motors.rotate(1.0);
      motors.wait();
    }
  }
  else
  {
    while (abs(compass.heading() - initialHeading) > 2.0)
    {
      motors.rotate(-1.0);
      motors.wait();
    }
  }
  
  motors.straight(47.0);
  motors.wait();
  
  /* Drop can etc... */
  closeArm.write(45);
  delay(400);
  motors.swingWithLeft(-90.0);
  motors.wait();
  
  digitalWrite(13, HIGH);
  while (true) {} // End of program, no need to loop
}

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  Wire.begin();
  motors.setup();
  closeArm.attach(3);
  Scheduler.startLoop(runMotors);

  /* Just to indicate the program is about to start */
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);
  delay(250);
}

void loop()
{
  endTile(false);
}

void runMotors()
{
  motors.run();
  yield();
}



float degreesToRotateToTargetCompassDirection(float target) {
    float current = compass.heading();    
    
    float currentRelativeHeading = current - target;
    if (currentRelativeHeading < 0) {
      currentRelativeHeading = currentRelativeHeading + 360;
    }
    
    float closest360;
    if(currentRelativeHeading>180) closest360 = 360;
    else closest360 = 0;
    
    return (closest360 - currentRelativeHeading);
}