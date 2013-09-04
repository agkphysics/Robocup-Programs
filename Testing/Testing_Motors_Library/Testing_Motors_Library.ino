#include <Scheduler.h>
#include <AccelStepper.h>
#include <Motors.h>


AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);
Motors motors(leftMotor, rightMotor);

void setup() {
  Scheduler.startLoop(runMotorLoop);
  motors.setup();
}

float leftSpeed = 600;
float rightSpeed = 600;

void loop() {
  motors.setActiveSpeeds(leftSpeed, rightSpeed);
  if (leftSpeed > -200 || rightSpeed >-200) {
    leftSpeed = leftSpeed-1;
    rightSpeed = rightSpeed-1;
  }
  delay(10);
}

void runMotorLoop() {
  motors.run();
  yield();
}
