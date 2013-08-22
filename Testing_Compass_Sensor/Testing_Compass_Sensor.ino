#include <Compass.h>
#include <Wire.h>
#include <Motors.h>
#include <AccelStepper.h>
#include <Scheduler.h>

Compass compass;
AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);
Motors motors(leftMotor, rightMotor);


void setup() {
  Serial.begin(9600);
  Wire.begin();
  Scheduler.startLoop(runMotorLoop);
  motors.setup();
}

void loop(){
  Serial.print(compass.heading());
  Serial.println(" heading");
  delay(100);
  motors.rotate(-compass.heading());
  delay(5000);
}


void runMotorLoop() {
  motors.run();
  yield();
}
