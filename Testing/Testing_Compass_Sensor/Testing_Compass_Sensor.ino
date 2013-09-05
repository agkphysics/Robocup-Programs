#include <Compass.h>
#include <Wire.h>
#include <Motors.h>
#include <AccelStepper.h>
#include <Scheduler.h>

Compass compass;
AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);
Motors motors(leftMotor, rightMotor);

int _initialHeading;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Scheduler.startLoop(runMotorLoop);
  motors.setup();
  _initialHeading = (int)(compass.heading());
}

void loop(){


  delay(100);
  float currentHeading = compass.heading();
  float degreesToRotate = degreesToNearest90();
  Serial.print(degreesToRotate);
  motors.rotate(degreesToRotate);
  motors.wait();
  delay(500);
    Serial.print(" heading");
    Serial.print(currentHeading);
    Serial.println(" ");
}


void runMotorLoop() {
  motors.run();
  yield();
}

	 
float degreesToNearest90() {
    int currentHeading = (int)(compass.heading());
	
    int currentRelativeHeading = currentHeading - _initialHeading;
    if (currentRelativeHeading < 0) {
      currentRelativeHeading = currentRelativeHeading + 360;
    }
	
    int closest90 = ((currentRelativeHeading + 45)/90)*90;
    return (float)(closest90 - currentRelativeHeading);
}
