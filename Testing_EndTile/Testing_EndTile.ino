#include <Servo.h>
#include <Scheduler.h>
#include <Compass.h>
#include <Wire.h>
#include <Motors.h>
#include <Ultrasonic.h>
#include <AccelStepper.h>

Ultrasonic ultrasonic(11, 12);

AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);

Compass compass;
float initialHeading;

Motors motors(leftMotor, rightMotor);
Servo closeArm;

void endTile()
{
  initialHeading = compass.heading();
  
  motors.setSpeeds(500, 500);
  motors.straight(0.0);
  motors.rotate(-90.0);
  motors.wait();
  
  motors.setSpeeds(50, 50);
  motors.rotate(180.0);
  float dist = ultrasonic.distance();
  float headingToCan = 0.0;
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
  float finishHeading = compass.heading();
  
  motors.setSpeeds(500, 500);
  if (finishHeading < headingToCan) motors.rotate(-(finishHeading + 360.0 - headingToCan));
  else motors.rotate(-(finishHeading - headingToCan));
  motors.wait();
  
  float distToCan = ultrasonic.distance();
  motors.rotate(-15.0);
  motors.wait();
  motors.straight(distToCan);
  motors.wait();
  delay(250);
  
  closeArm.write(90);
  delay(1000);
  
  /* Lift arm etc... */
  
  motors.straight(-distToCan);
  motors.wait();
  if (headingToCan < initialHeading) motors.rotate(initialHeading - headingToCan);
  else motors.rotate(initialHeading + 360.0 - headingToCan);
  motors.wait();
  
  digitalWrite(13, HIGH);
  delay(1000);
}

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  Wire.begin();
  motors.setup();
  closeArm.attach(www);
  Scheduler.startLoop(runMotors);

  /* Just to indicate the program is about to start */
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);
  delay(250);
}

void loop()
{
  endTile();
}

void runMotors()
{
  motors.run();
  yield();
}

