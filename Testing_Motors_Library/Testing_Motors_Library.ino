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

void loop() {
  motors.rotate(90.0);
  motors.wait();
  motors.straight(10.0);
  motors.wait();
  motors.swingWithLeft(90.0);
  motors.wait();
  motors.straight(10);
  motors.wait();
  motors.rotate(90);
  motors.wait();
  motors.swingWithRight(90);
  motors.wait();
  delay(5000);
}

void runMotorLoop() {
  motors.run();
  yield();
}
