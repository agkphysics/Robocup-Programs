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

#define PIN_COLOUR_LEFT 52
#define PIN_COLOUR_RIGHT 50
#define PIN_LEOSTICK_EXTRA 48
#define PIN_LIFT_MOTOR 32
#define PIN_TOWER_SWITCH 28
#define PIN_BOARD_LED 13

void definePins() {
  pinMode(PIN_COLOUR_LEFT, INPUT);
  pinMode(PIN_COLOUR_RIGHT, INPUT);
  pinMode(PIN_LEOSTICK_EXTRA, INPUT);
  pinMode(PIN_LIFT_MOTOR, OUTPUT);
  pinMode(PIN_TOWER_SWITCH, INPUT);
  pinMode(PIN_BOARD_LED, OUTPUT);
  
  digitalWrite(PIN_LIFT_MOTOR, LOW);
}
  

Compass compass;
float initialHeading;

void endTile(boolean left)
{
  initialHeading = compass.heading();
  
  motors.setMaxSpeeds(2500, 2500);
  motors.straight(0.0);
  
  if (left) motors.rotate(-90.0);
  motors.wait();
  
  motors.setMaxSpeeds(150, 150);
  
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
      
      motors.setMaxSpeeds(2000, 2000);
      motors.rotate(-90);
      motors.wait();
      delay(2000);
      motors.setMaxSpeeds(150, 150);
      motors.rotate(90.0);
    }
  }
  float finishHeading = compass.heading();
  
  motors.setMaxSpeeds(750, 750);

  //motors.rotate(degreesToRotateToTargetCompassDirection(headingToCan));
  //*
  while (abs(compass.heading() - headingToCan) > 2.0)
  {
    motors.rotate(-1.0);
    motors.wait();
  }
  //*/
  
  /* An extra few degrees just in case... */
  if (dist >= 40.0) motors.rotate(0.0);
  else motors.rotate(-8.0);
  motors.wait();
  
  float distToCan = dist;
  motors.straight(distToCan);
  motors.wait();
  
  /* Swing to the right in case the can is too far right */
  if (dist >= 40.0) motors.swingWithLeft(45.0);
  else motors.swingWithLeft(45.0);
  motors.wait();
  delay(250);
  
  closeArm.write(0); // MUST be 0, not 180!
  delay(750);
  
  motors.setMaxSpeeds(2500, 2500);
  if (dist >= 40.0) motors.swingWithLeft(-45.0);
  else motors.swingWithLeft(-45.0);
  motors.wait();
  
  motors.straight(0.0);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  
  /* Lift arm */
  digitalWrite(PIN_LIFT_MOTOR, HIGH);
  delayMicroseconds(4000000);
  digitalWrite(PIN_LIFT_MOTOR, LOW);

  motors.straight(-distToCan);
  motors.wait();
  
  if (left) motors.rotate(-10.0);
  else motors.rotate(10.0);
  
  //motors.rotate(degreesToRotateToTargetCompassDirection(initialHeading));
  //*
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
  //*/
  
  motors.straight(47.0);
  motors.wait();
  
  /* Drop can etc... */
  closeArm.write(60);
  delay(400);
  motors.swingWithLeft(-20.0);
  motors.wait();
  
  motors.straight(-15.0);
  motors.wait();
  
  digitalWrite(PIN_BOARD_LED, HIGH);
  while (true) {} // End of program, no need to loop
}

void setup()
{
  definePins();
  digitalWrite(PIN_BOARD_LED, LOW);
  
  Wire.begin();
  motors.setup();
  closeArm.attach(3);
  closeArm.write(60);
  delay(500);
  Scheduler.startLoop(runMotors);

  /* Just to indicate the program is about to start */
  digitalWrite(PIN_BOARD_LED, HIGH);
  delay(250);
  digitalWrite(PIN_BOARD_LED, LOW);
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
